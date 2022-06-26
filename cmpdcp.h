#ifndef CMPDCP_H_
#define CMPDCP_H_

#include "list.h"
#include "utils.h"
#include <string>
class CMPDCP
{
public:
    CMPDCP();
    ~CMPDCP();
    void compression();
    void decompression();

private:
    const char ch = 'T';
    int t;
    string fl, bits;
    List<BinarySearchTree<Fileinfo<int>>> *ls;
    void createHuffmanTree();
};
#endif //CMPDCP_H_