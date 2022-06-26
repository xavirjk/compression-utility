#include "utils.h"
#include <fstream>
#include <iostream>
using namespace std;

int binToDec(string str)
{
    string num = str;
    int dec_value = 0;
    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--)
    {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    return dec_value;
}
void toByte(string tree, string str)
{
    int N = int(str.size());
    if (N % 8 != 0)
        return;
    string res = "";
    for (int i = 0; i < N; i += 8)
    {
        int decimal_value = binToDec((str.substr(i, 8)));
        res += char(decimal_value);
    }
    fstream fs;
    fs.open("E:\\qt-rec\\413_test\\output.txt");
    if (!fs)
    {
        cout << "fopen() failed for writing";
        exit(EXIT_FAILURE);
    }
    std::ostream &os = std::cout;
    os << endl
       << tree << " " << res << endl;
    fs << tree << " " << res;
    fs.close();

    string sc = readFile("E:\\qt-rec\\413_test\\output.txt");
    os << "*****" << endl
       << sc << endl
       << "*****" << endl;
    cout << "*****" << endl
         << sc << endl
         << "*****" << endl;
}
string readFile(string path)
{
    constexpr auto readSize = size_t(4096);
    auto stream = ifstream(path.data());
    stream.exceptions(ios_base::badbit);
    auto out = string();
    auto buf = string(readSize, '\0');
    while (stream.read(&buf[0], readSize))
    {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}