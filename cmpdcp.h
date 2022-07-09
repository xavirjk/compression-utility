#ifndef CMPDCP_H_
#define CMPDCP_H_

#include "cmpdcp_lib_global.h"
#include "list.h"
#include "utils.h"
#include <string>
class HCAPI CMPDCP
{
public:
    CMPDCP(const string &fn = string());
    ~CMPDCP();
    void compression();
    void decompression();

private:
    const char ch = 'T';
    const string path;
    int t;
    string fl, bits;
    List<BTree<Fileinfo<int>>> *ls;
    Huffman *hf;
    void createHuffmanTree();
};
#endif //CMPDCP_H_