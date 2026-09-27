#include <unistd.h>
#include "rmalloc.h"

#include <iostream>

Chunk* BASE = new Chunk(0);
int num_chunks = 0;

void* rmalloc(int alloc_size) {
    void* addr = nullptr;
    Chunk* tmp = BASE;
    while(tmp->next != nullptr && (tmp->occupied == true || tmp->chunklen < alloc_size)) {
        tmp = tmp->next;
    }
    if(tmp == BASE || (tmp->next == nullptr && (tmp->occupied == true || tmp->chunklen < alloc_size))) {
        addr = sbrk(alloc_size);
        tmp->next = new Chunk(true, alloc_size, addr, tmp);
        num_chunks++;
    } else {
        addr = tmp->addr;
    }
    return addr;
}

void rfree(void* ptr) {
    Chunk* tmp = BASE;
    while(tmp->addr != ptr) {
        tmp = tmp->next;
    }
    tmp->occupied = false;
}

// Testing section below

// #include <ostream>

// std::ostream& operator<<(std::ostream& out, Chunk& c) {
//     out << "Chunk ->\n";
//     out << std::boolalpha;
//     out << "occupied = " << c.occupied << std::endl;
//     out << "chunklen = " << c.chunklen << std::endl;
//     return out;
// }

int main() {
    // Chunk c{false, 2};
    // std::cout << c;

    void* mem = rmalloc(sizeof(int));
    // void* mem2 = rmalloc(4*sizeof(int));
    // void* mem3 = rmalloc(sizeof(int));
    // void* mem4 = rmalloc(sizeof(int));
    // void* mem5 = rmalloc(sizeof(int));
    // void* mem6 = rmalloc(sizeof(int));
    std::cout << mem << std::endl;
    // std::cout << mem2 << std::endl;
    // std::cout << mem3 << std::endl;
    // std::cout << mem4 << std::endl;
    // std::cout << mem5 << std::endl;
    // std::cout << mem6 << std::endl;
    std::cout << num_chunks << std::endl;


    rfree(mem);
    // rfree(mem2);
    // rfree(mem3);
    // rfree(mem4);
    // rfree(mem5);
    // rfree(mem6);
    
    return 0;
}

