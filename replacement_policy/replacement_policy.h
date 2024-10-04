#ifndef REPLACEMENT_POLICY_H
#define REPLACEMENT_POLICY_H

#include <list>
#include <cstdint>

class ReplacementPolicy {
public:
    virtual bool find_block(std::list<uint64_t>& set, uint64_t block_addr) = 0;
    virtual void replace_block(std::list<uint64_t>& set, uint64_t block_addr, size_t associativity) = 0;
    virtual ~ReplacementPolicy() = default;
};

#endif  // REPLACEMENT_POLICY_H
