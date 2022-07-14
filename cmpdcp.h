#ifndef CMPDCP_H_
#define CMPDCP_H_

#include "cmpdcp_lib_global.h"
#include "list.h"
#include <string>
#include <fstream>
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
    int t, size, start;
    string fl, bits, file_extension;
    List<BTree<Fileinfo<int>>> *ls;
    BTree<Fileinfo<int>> *tree;
    Huffman *hf;

    bool _canonize = true;

    void createHuffmanTree();
    void canonizeHuffman();
    void writeHead(ofstream &out);
    void writeBody(ofstream &out);
    int findChar(char s);
    int binToDec(string str);
    int _pow(int c, int base = 2);
    string appendBits(string &bits);
    string readFile(string path);
    void readHead();
    void readBody(ofstream &out);
    string binary_string(int n);
    string Dcd(string ec);
};
#endif //CMPDCP_H_