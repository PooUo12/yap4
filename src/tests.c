#define _DEFAULT_SOURCE

#include "tests.h"

bool test1() {
    //new heap
    void *heap = heap_init(2048);
    if (heap == NULL) return false;
    debug_heap(stdout, heap);
    //new block
    void *block = _malloc(512);
    if (block == NULL) return false;
    debug_heap(stdout, heap);
    //free block
    _free(block);
    debug_heap(stdout, heap);

    munmap(heap, REGION_MIN_SIZE);
    return true;
}

bool test2() {
    //new heap
    void *heap = heap_init(2048);
    if (heap == NULL) return false;
    //two new blocks
    void *block1 = _malloc(256);
    void *block2 = _malloc(128);
    if (block1 == NULL || block2 == NULL) return false;
    debug_heap(stdout, heap);
    //free first one
    _free(block1);
    debug_heap(stdout, heap);

    munmap(heap, REGION_MIN_SIZE);
    return true;

}

bool test3() {
    //new heap
    void *heap = heap_init(2048);
    if (heap == NULL) return false;
    //three new blocks
    void *block1 = _malloc(128);
    void *block2 = _malloc(256);
    void *block3 = _malloc(512);
    if (block1 == NULL || block2 == NULL || block3 == NULL) return false;
    debug_heap(stdout, heap);
    //free first and third
    _free(block1);
    debug_heap(stdout, heap);

    _free(block3);
    debug_heap(stdout, heap);

    munmap(heap, REGION_MIN_SIZE);
    return true;

}

bool test4() {
    //new very small heap
    void *heap = heap_init(128);
    if (heap == NULL) return false;
    debug_heap(stdout, heap);
    //new block bigget than heap
    void *block1 = _malloc(REGION_MIN_SIZE + 512);
    if (block1 == NULL) return false;
    debug_heap(stdout, heap);
    //free new block
    _free(block1);
    munmap(heap, 2 * REGION_MIN_SIZE);
    return true;
}

bool test5() {
    //new very small heap
    void *heap = heap_init(128);
    if (heap == NULL) return false;
    debug_heap(stdout, heap);
    //new region so that unable to gather old and new heap
    (void) mmap(heap + REGION_MIN_SIZE, REGION_MIN_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
    //new block
    void *block1 = _malloc(4096);
    if (block1 == NULL) return false;
    debug_heap(stdout, heap);

    munmap(heap, REGION_MIN_SIZE);
    return true;

}