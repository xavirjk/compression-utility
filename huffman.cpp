#include "huffman.h"
Huffman::Huffman(){};
Huffman::~Huffman(){};
int Huffman::getFrequency() const { return 1; }
bool Huffman::flagged() const { return false; }
void Huffman::flag() {}
bool Huffman::findSymbol(char ch) const { return false; }
void Huffman::print() const {}