#include "huffman.h"
Huffman::Huffman(const std::string &code, const char &symbol) : code(code), symbol(symbol){};

Huffman::~Huffman(){};

bool Huffman::findSymbol(char ch) const { return ch == symbol; }

void Huffman::print() const { std::cout << symbol << " " << code << std::endl; }

void Huffman::setData(const char &s, const std::string &c)
{
    symbol = s;
    code = c;
}

std::string Huffman::coded() const
{
    return code;
}

char Huffman::getSymbol() const { return symbol; }
