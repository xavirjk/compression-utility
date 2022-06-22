#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include "string"
#include "entity.h"
class Huffman : public Entity
{
public:
    Huffman();
    ~Huffman();

    int getFrequency() const override;
    void flag() override;
    bool flagged() const override;
    bool findSymbol(char ch) const override;
    void print() const override;

private:
    std::string code;
    char symbol;
};

#endif //HUFFMAN_H_