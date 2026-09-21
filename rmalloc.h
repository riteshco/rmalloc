#ifndef HEADER_H
#define HEADER_H

class Chunk {
    public:
        bool occupied;
        int chunklen;
        Chunk* next{nullptr};
        Chunk* prev{nullptr};

        Chunk(int c): chunklen(c) {
            occupied = true;
        }

        Chunk(bool b, int c): occupied(b), chunklen(c) {}
        
        Chunk(bool b, int c, Chunk* prev) : occupied(b), chunklen(c), prev(prev) {}
};

void* rmalloc(int alloc_size);
void rfree(void* ptr);

#endif
