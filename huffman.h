#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include "string"
#include "entity.h"
#include <iostream>
using namespace std;
class Huffman : public Entity
{
public:
    Huffman(const string &code = string(), const char &symbol = char());
    ~Huffman();

    int getFrequency() const override;
    void flag() override;
    bool flagged() const override;
    bool findSymbol(char ch) const override;
    void print() const override;
    string coded() const;
    char getSymbol() const;

    void setData(const char &s = char(), const string &c = string());

private:
    string code;
    char symbol;
};

#endif //HUFFMAN_H_