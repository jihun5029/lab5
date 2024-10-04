#ifndef TLB_H
#define TLB_H

#include <unordered_map>

class TLB {
public:
    TLB(size_t size) : size(size) {}

    int translate(uint64_t virtual_page) {
        if (tlb.find(virtual_page) != tlb.end()) {
            return tlb[virtual_page];
        }
        return -1;
    }

    void add_entry(uint64_t virtual_page, int physical_page) {
        if (tlb.size() >= size) {
            tlb.erase(tlb.begin());  // TLB가 가득 차면 첫 번째 항목 제거
        }
        tlb[virtual_page] = physical_page;
    }

private:
    size_t size;
    std::unordered_map<uint64_t, int> tlb;
};

#endif  // TLB_H
