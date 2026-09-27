#ifndef HEADER_H
#define HEADER_H

class Chunk {
    public:
        bool occupied;
        int chunklen;
        void* addr;
        Chunk* next{nullptr};
        Chunk* prev{nullptr};

        Chunk(int c): chunklen(c) {
            occupied = true;
        }

        Chunk(bool b, int c): occupied(b), chunklen(c) {}
        
        Chunk(bool b, int c, void* addr) : occupied(b), chunklen(c), addr(addr) {}

        Chunk(bool b, int c, void* addr, Chunk* prev) : occupied(b), chunklen(c), addr(addr), prev(prev) {}
};

void* rmalloc(int alloc_size);
void rfree(void* ptr);

#endif
