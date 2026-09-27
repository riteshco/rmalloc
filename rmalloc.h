#ifndef HEADER_H
#define HEADER_H

class Chunk {
    public:
        bool occupied;
        int chunklen;
        Chunk* next{nullptr};
        Chunk* prev{nullptr};
};

inline int num_chunks = 0;

void* rmalloc(int alloc_size);
void rfree(void* ptr);

#endif
