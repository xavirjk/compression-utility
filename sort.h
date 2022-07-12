#ifndef SORT_H
#define SORT_H

#include "huffman.h"

namespace MP
{
    namespace sort
    {
        class HeapSort
        {
        public:
            HeapSort();
            ~HeapSort();

            void createMax_Heap(int len);
            void max_Heapify(int i, int n);
            void sort_MaxHeap(int n);
            void swap(int a, int b);
            void heapSort(Huffman *staticArr, int len, bool _chsort = false, int start = 0);

        private:
            Huffman *dataset;
            bool cHsort;
            int start;
        };

    }
}

#endif // SORT_H
