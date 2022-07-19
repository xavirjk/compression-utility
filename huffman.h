#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <string>
#include <iostream>
class Huffman
{
public:
    Huffman(const std::string &code = std::string(), const char &symbol = char());
    ~Huffman();

    bool findSymbol(char ch) const;
    void print() const;
    std::string coded() const;
    char getSymbol() const;

    void setData(const char &s = char(), const std::string &c = std::string());

private:
    std::string code;
    char symbol;
};

#endif //HUFFMAN_H_