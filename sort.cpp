#include "sort.h"
using namespace MP::sort;
HeapSort::HeapSort() {}
HeapSort::~HeapSort() {}

void HeapSort::swap(int a, int b)
{
    Huffman temp = dataset[a];
    dataset[a] = dataset[b];
    dataset[b] = temp;
}
void HeapSort::createMax_Heap(int len)
{
    for (int i = len / 2 - 1; i >= 0; i--)
    {
        max_Heapify(i, len);
    }
}

void HeapSort::max_Heapify(int i, int n)
{
    int largest = i + start;
    int left = (2 * i) + 1 + start;
    int right = (2 * i) + 2 + start;
    //If left child is larger than Root
    if (left < n + start)
    {
        bool lTruthy;
        if (cHsort)
            lTruthy = dataset[left].getSymbol() > dataset[largest].getSymbol();
        else
            lTruthy = dataset[left]._len() > dataset[largest]._len();
        if (lTruthy)
            largest = left;
    }
    //if right child is larger than largest So far
    if (right < n + start)
    {
        bool rTruthy;
        if (cHsort)
            rTruthy = dataset[right].getSymbol() > dataset[largest].getSymbol();
        else
            rTruthy = dataset[right]._len() > dataset[largest]._len();
        if (rTruthy)
            largest = right;
    }
    if (largest != i + start)
    {
        swap(i + start, largest);
        max_Heapify(largest, n);
    }
}
void HeapSort::sort_MaxHeap(int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        swap(0 + start, i + start);
        createMax_Heap(i);
    }
}
void HeapSort::heapSort(Huffman *staticArr, int len, bool _chsort, int _start)
{
    cHsort = _chsort;
    start = _start;
    dataset = staticArr;
    createMax_Heap(len);
    sort_MaxHeap(len);
}
