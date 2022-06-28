#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include "fileinfo.h"

int binToDec(std::string str);
void toByte(std::string tree, std::string str);
std::string readFile(std::string path);
std::string Dcd(std::string ec);
std::string appendBits(std::string &bits, int num = 8);
int _pow(int c, int base = 2);
std::string toCharStr(int num);
Fileinfo<int> getInfo(char ch = 'T', int t = -1);
void writeFile(std::string path, std::string data);

#endif //UTILS_H_