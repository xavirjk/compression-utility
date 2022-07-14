#include "huffman.h"
Huffman::Huffman(const string &code, const char &symbol) : code(code), symbol(symbol){};
Huffman::~Huffman(){};
int Huffman::getFrequency() const { return 1; }
bool Huffman::flagged() const { return false; }
void Huffman::flag() {}
bool Huffman::findSymbol(char ch) const { return ch == symbol; }
void Huffman::print() const
{
    cout << symbol << " " << code << endl;
}

void Huffman::setData(const char &s, const string &c, bool canonical)
{
    cout << s << ":" << c << endl;
    symbol = s;
    if (canonical)
        len = c.length();
    else
        code = c;
}

string Huffman::coded() const
{
    return code;
}

char Huffman::getSymbol() const
{
    return symbol;
}
int Huffman::_len() const
{
    return len;
}
void Huffman::canonicalCodes(const string &c) { code = c; }