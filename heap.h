// Code written by Aaron Bloomfield, 2014
// Released under a CC BY-SA license
// This code is part of the https://github.com/aaronbloomfield/pdr repository


//Rehan Javaid, rj3dxu, 11/11/2020, heap.h

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "huffmanenc.h"
using namespace std;

class binary_heap {
public:
    binary_heap();
    binary_heap(vector<huffman_node*> vec);
    ~binary_heap();

    void insert(huffman_node* x);
    huffman_node* findMin();
    huffman_node* deleteMin();
    unsigned int size();
    void makeEmpty();
    bool isEmpty();
    void print();

private:
    vector<huffman_node*> heap;
    unsigned int heap_size;

    void percolateUp(int hole);
    void percolateDown(int hole);
};

#endif
