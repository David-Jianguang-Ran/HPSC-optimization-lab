//
// Created by dran on 10/9/23.
// everything is in headers because Scott is lazy and doesn't want complicated makefile.
//

#ifndef HPSC_OPTIMIZATION_LAB_CONTIGUOUSARRAY_H
#define HPSC_OPTIMIZATION_LAB_CONTIGUOUSARRAY_H

#include <memory.h>

// remember we use 1 based indexing here
template <typename DT>
class Contiguous2DArray {
public:
    // the attrs are public, but you really shouldn't access directly
    DT* content;
    int x_max;
    int y_max;

    Contiguous2DArray();
    Contiguous2DArray(int x_max, int y_max, bool zero_out = false);
    ~Contiguous2DArray();

    // for iterating over continuous ranges, like an iterator
    inline DT* get_ptr(int x, int y);
    // for single element access
    inline DT& at(int x, int y);

    void swap(Contiguous2DArray<DT>& other);
};

// zig zag array
//
template <typename DT>
class ZigZagArray : Contiguous2DArray<DT> {

public:
    inline DT& at(int x, int y) {
        return this->content + y % 2 + y / 2 * 2 * this->x_max + x * 2;
    }
};



// implementations

template <typename DT>
Contiguous2DArray<DT>::Contiguous2DArray() {
    // fake constructor, make sure to really do it later
}

template <typename DT>
Contiguous2DArray<DT>::Contiguous2DArray(int x_max, int y_max, bool zero_out) {
    this->content = new DT[x_max * y_max];
    this->x_max = x_max;
    this->y_max = y_max;
    if (zero_out)
        memset(this->content, 0, sizeof(DT) * x_max * y_max);  // Does this get vectorization during optimizing passes?
}

template <typename DT>
Contiguous2DArray<DT>::~Contiguous2DArray() {
    delete[] this->content;
}

template <typename DT>
inline DT* Contiguous2DArray<DT>::get_ptr(int y, int x) {
    return this->content + (y - 1) * this->x_max + (x - 1);
}

template <typename DT>
inline DT& Contiguous2DArray<DT>::at(int y, int x) {
    return this->content[(y - 1) * this->x_max + (x - 1)];
}

template <typename DT>
void Contiguous2DArray<DT>::swap(Contiguous2DArray<DT>& other) {
    DT* temp = this->content;
    this->content = other.content;
    other.content = temp;
}

#endif //HPSC_OPTIMIZATION_LAB_CONTIGUOUSARRAY_H
