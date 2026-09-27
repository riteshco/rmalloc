#include "rmalloc.h"
#include <iostream>
#include <ostream>

std::ostream& operator<<(std::ostream& out, Chunk& c) {
    out << "Chunk ->\n";
    out << std::boolalpha;
    out << "occupied = " << c.occupied << std::endl;
    out << "chunklen = " << c.chunklen << std::endl;
    return out;
}

int main() {
    // Chunk c{false, 2};
    // std::cout << c;

    void* mem = rmalloc(sizeof(int));
    void* mem2 = rmalloc(32*sizeof(int));
    void* mem3 = rmalloc(sizeof(int));
    rfree(mem2);
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
    rfree(mem4);
    rfree(mem5);
    rfree(mem3);
    rfree(mem6);
    
    return 0;
}