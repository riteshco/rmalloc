#include "rmalloc.h"

void* rmalloc(int alloc_size) {
    return nullptr;
}

void rfree(void* ptr) {}

// Testing section below

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
    Chunk c{false, 2};
    std::cout << c;
    return 0;
}

