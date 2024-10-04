#ifndef TRACEREADER_H
#define TRACEREADER_H

#include <fstream>
#include <string>

struct Instruction {
    // You must complete this section of the code //   
    // Above //

    // Below //   
};

class TraceReader {
public:
    TraceReader(const std::string& trace_file);
    ~TraceReader();

    bool get_next_instruction(Instruction& instr);


private:
    std::ifstream trace_stream;
};

#endif  // TRACEREADER_H
