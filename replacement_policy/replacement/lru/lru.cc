#include "lru.h"
#include <algorithm>

bool LRU::find_block(std::list<uint64_t>& set, uint64_t block_addr) {
    auto it = std::find(set.begin(), set.end(), block_addr);
    if (it != set.end()) {
        set.erase(it);  // 기존 위치에서 삭제하고
        set.push_back(block_addr);  // 가장 최근에 사용된 위치로 이동
        return true;
    }
    return false;
}

void LRU::replace_block(std::list<uint64_t>& set, uint64_t block_addr, size_t associativity) {
    if (set.size() >= associativity) {
        set.pop_front();  // 가장 오래된 블록을 제거
    }
    set.push_back(block_addr);  // 새로운 블록 추가
}
