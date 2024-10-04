#include "src/cache.h"
#include "src/tlb.h"
#include "trace_read/tracereader.h"
#include "replacement_policy/replacement_policy.h"
#include "replacement_policy/replacement/fifo/fifo.h"
#include "replacement_policy/replacement/lru/lru.h"
#include "nlohmann/json.hpp"

#include <iostream>
#include <memory>
#include <fstream>

// nlohmann/json namespace alias
using json = nlohmann::json;

void save_results(const std::string& output_file, const Instruction& instr) {
    
    // You must complete this section of the code //   
    // Above //

    // Below //   
  
}


void save_final_results(const std::string& output_file, int l1_hits, int l1_misses, int l2_hits, int l2_misses, int l2_accesses) {
        
    // You must complete this section of the code //   
    // Above //

    // Below //   
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>\n";
        return 1;
    }

    // argv[1] == config.json file
    std::string config_file = argv[1];
    
    // You need to write the part that reads and processes the JSON file.
    
    // Above //

    // Below //   


    CacheHierarchy cache_hierarchy(l1_cache_size, block_size, l1_assoc, l2_cache_size, block_size, l2_assoc, replacement_policy); 
    TLB tlb(tlb_size);
    TraceReader reader(trace_file);
    Instruction instr;

    int l1_hits = 0, l1_misses = 0, l2_hits = 0, l2_misses = 0;
    int total_instructions = 0, l2_accesses = 0;

    while (reader.get_next_instruction(instr)) {

        int physical_page = tlb.translate(instr.mem_addr / block_size);
        if (physical_page == -1) {
            physical_page = instr.mem_addr / block_size;
            tlb.add_entry(instr.mem_addr / block_size, physical_page);
        }


        if (cache_hierarchy.l1_access(physical_page * block_size)) {
            instr.cache_l1_hit = true;
            instr.cache_l1_miss = false;
            instr.cache_l2_hit = false;
            instr.cache_l2_miss = false;
            l1_hits++;
        } else {
            instr.cache_l1_hit = false;
            instr.cache_l1_miss = true;
            l1_misses++;
            l2_accesses++;  


            if (cache_hierarchy.l2_access(physical_page * block_size)) {
                instr.cache_l2_hit = true;
                instr.cache_l2_miss = false;
                l2_hits++;
            } else {
                instr.cache_l2_hit = false;
                instr.cache_l2_miss = true;
                l2_misses++;
                cache_hierarchy.memory_access(physical_page * block_size);
            }
        }

        total_instructions++;
        save_results(output_file, instr); 
    }

    save_final_results(output_file, l1_hits, l1_misses, l2_hits, l2_misses, l2_accesses);

    return 0;
}
