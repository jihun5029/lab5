#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <iostream>
#include <memory>
#include <list>
#include "../replacement_policy/replacement_policy.h"

class CacheHierarchy {
public:
    CacheHierarchy(size_t l1_size, size_t l1_block_size, size_t l1_assoc, size_t l2_size, size_t l2_block_size, size_t l2_assoc, std::shared_ptr<ReplacementPolicy> rp)
        : l1_cache(l1_size, l1_block_size, l1_assoc, rp), l2_cache(l2_size, l2_block_size, l2_assoc, rp), l1_hits(0), l1_misses(0), l2_hits(0), l2_misses(0) {}

    bool l1_access(uint64_t mem_addr) {
        return l1_cache.access(mem_addr);
    }

    bool l2_access(uint64_t mem_addr) {
        return l2_cache.access(mem_addr);
    }

    void memory_access(uint64_t mem_addr) {
        l2_cache.add(mem_addr);
        l1_cache.add(mem_addr);
    }

private:
    class Cache {
    public:
        Cache(size_t size, size_t block_size, size_t associativity, std::shared_ptr<ReplacementPolicy> rp)
            : size(size), block_size(block_size), associativity(associativity), num_sets(size / (block_size * associativity)), rp(rp) {
            cache.resize(num_sets);
        }

        bool access(uint64_t mem_addr) {
            uint64_t block_addr = mem_addr / block_size;
            uint64_t set_index = block_addr % num_sets;
            auto& set = cache[set_index];

            return rp->find_block(set, block_addr);
        }

        void add(uint64_t mem_addr) {
            uint64_t block_addr = mem_addr / block_size;
            uint64_t set_index = block_addr % num_sets;
            auto& set = cache[set_index];

            rp->replace_block(set, block_addr, associativity);
        }

    private:
        size_t size;
        size_t block_size;
        size_t associativity;
        size_t num_sets;
        std::vector<std::list<uint64_t>> cache;
        std::shared_ptr<ReplacementPolicy> rp;
    };

    Cache l1_cache;
    Cache l2_cache;

    int l1_hits;
    int l1_misses;
    int l2_hits;
    int l2_misses;
};

#endif  // CACHE_H
