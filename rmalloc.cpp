#include <unistd.h>
#include "rmalloc.h"

Chunk* head = nullptr;

static Chunk* findFreeChunk(Chunk* head, int alloc_size) {
    while(head->next != nullptr && (head->occupied == true || head->chunklen < alloc_size)) {
        head = head->next;
    }
    return head;
}

static void splitChunk(Chunk* chunk, unsigned int req_size) {
    void* breakpoint = (char* )(chunk+1) + req_size;
    Chunk* newChunk = (Chunk*)breakpoint;
    newChunk->chunklen = chunk->chunklen - req_size - sizeof(Chunk);
    chunk->chunklen = req_size;
    newChunk->next = chunk->next;
    if(newChunk->next) newChunk->next->prev = newChunk;
    chunk->next = newChunk;
    newChunk->prev = chunk;
    newChunk->occupied = false;
    num_chunks++;
}

static void mergeChunkNext(Chunk* chunk) {
    if(chunk->next != nullptr && chunk->next->occupied == false) {
        chunk->chunklen += sizeof(Chunk) + chunk->next->chunklen;
        if(chunk->next->next) chunk->next->next->prev = chunk;
        chunk->next = chunk->next->next;
        num_chunks--;
    }
}

static Chunk* mergeChunkPrev(Chunk* chunk) {
    if(chunk->prev != nullptr && chunk->prev->occupied == false) {
        chunk->prev->chunklen += sizeof(Chunk) + chunk->chunklen;
        chunk->prev->next = chunk->next;
        if(chunk->next) chunk->next->prev = chunk->prev;
        chunk = chunk->prev;
        num_chunks--;
    }
    return chunk;
}

void* rmalloc(int alloc_size) {
    void* addr = nullptr;
    Chunk* tmp = head;
    if(tmp == nullptr) {
        head = (Chunk*)sbrk(sizeof(Chunk));
        addr = sbrk(alloc_size);
        head->chunklen = alloc_size;
        head->occupied = true;
        num_chunks++;
    } else {
        tmp = findFreeChunk(tmp, alloc_size);
        if(tmp->next == nullptr && (tmp->occupied == true || tmp->chunklen < alloc_size)) {
            Chunk* newchunk = (Chunk*)sbrk(sizeof(Chunk));
            addr = sbrk(alloc_size);
            newchunk->chunklen = alloc_size;
            newchunk->prev = tmp;
            newchunk->occupied = true;
            tmp->next = newchunk;
            num_chunks++;
        } else {
            if(tmp->chunklen > alloc_size + sizeof(Chunk)) {
                splitChunk(tmp, alloc_size);
            }
            addr = (void*)(tmp+1);
            tmp->occupied = true;
        }
    }
    return addr;
}

void rfree(void* ptr) {
    Chunk* tmp = head;
    while((void*)(tmp+1) != ptr) {
        tmp = tmp->next;
    }
    tmp->occupied = false;
    mergeChunkNext(tmp);
    tmp = mergeChunkPrev(tmp);
    if(tmp->next == nullptr) {
        if(tmp->prev != nullptr) tmp->prev->next = nullptr;
        else head = nullptr;
        brk(tmp);
    }
}

