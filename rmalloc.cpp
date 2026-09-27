#include <unistd.h>
#include "rmalloc.h"

#include <iostream>

Chunk* head = nullptr;
int num_chunks = 0;

void* rmalloc(int alloc_size) {
    void* addr = nullptr;
    Chunk* tmp = head;
    if(tmp == nullptr) {
        head = (Chunk*)sbrk(sizeof(Chunk));
        addr = sbrk(alloc_size);
        head->addr = addr;
        head->chunklen = alloc_size;
        head->occupied = true;
        num_chunks++;
    } else {
        while(tmp->next != nullptr && (tmp->occupied == true || tmp->chunklen < alloc_size)) {
            tmp = tmp->next;
        }
        if(tmp->next == nullptr) {
            Chunk* newchunk = (Chunk*)sbrk(sizeof(Chunk));
            addr = sbrk(alloc_size);
            newchunk->addr = addr;
            newchunk->chunklen = alloc_size;
            newchunk->prev = tmp;
            newchunk->occupied = true;
            tmp->next = newchunk;
            num_chunks++;
        } else {
            addr = tmp->addr;
            tmp->occupied = true;
        }
    }
    return addr;
}

void rfree(void* ptr) {
    Chunk* tmp = head;
    while(tmp->addr != ptr) {
        tmp = tmp->next;
    }
    tmp->occupied = false;
    if(tmp->next == nullptr) {
        brk(tmp);
    }
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
    void* mem2 = rmalloc(4*sizeof(int));
    void* mem3 = rmalloc(sizeof(int));
    void* mem4 = rmalloc(sizeof(int));
    void* mem5 = rmalloc(sizeof(int));
    void* mem6 = rmalloc(sizeof(int));
    std::cout << mem << std::endl;
    std::cout << mem2 << std::endl;
    std::cout << mem3 << std::endl;
    std::cout << mem4 << std::endl;
    std::cout << mem5 << std::endl;
    std::cout << mem6 << std::endl;
    std::cout << num_chunks << std::endl;


    rfree(mem);
    rfree(mem2);
    rfree(mem4);
    rfree(mem5);
    rfree(mem3);
    rfree(mem6);
    
    return 0;
}

