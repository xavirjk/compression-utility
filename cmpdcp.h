#ifndef CMPDCP_H_
#define CMPDCP_H_

#include "cmpdcp_lib_global.h"
#include "list.h"
#include <fstream>
#include <windows.h>
class HCAPI CMPDCP
{
public:
    CMPDCP(const std::string &fn = std::string());
    ~CMPDCP();
    void compression();
    void decompression();
    void cleanUp();
    LPCSTR statusMessage = "";

private:
    const char ch = 'T';
    const std::string path;
    int t, size, start;
    std::string fl, bits, file_extension;
    List<BTree<Fileinfo<int>>> *ls;
    BTree<Fileinfo<int>> *tree;
    Huffman *hf;

    void createHuffmanTree();
    void canonizeHuffman();
    void writeHead(std::ofstream &out);
    void writeBody(std::ofstream &out);
    int findChar(char s);
    int binToDec(std::string str);
    int _pow(int c, int base = 2);
    std::string appendBits(std::string &bits);
    void readFile(std::string path);
    void readHead();
    void readBody(std::ofstream &out);
    std::string binary_string(int n);
    std::string Dcd(std::string ec);
};
#endif //CMPDCP_H_