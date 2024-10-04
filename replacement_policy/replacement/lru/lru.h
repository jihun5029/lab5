#ifndef LRU_H
#define LRU_H

#include "../../replacement_policy.h"
#include <list>

class LRU : public ReplacementPolicy {
public:
    bool find_block(std::list<uint64_t>& set, uint64_t block_addr) override;
    void replace_block(std::list<uint64_t>& set, uint64_t block_addr, size_t associativity) override;
};

#endif  // LRU_H
