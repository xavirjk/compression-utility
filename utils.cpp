#include "utils.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include "bits/stdc++.h"
using namespace std;

int _pow(int c, int base)
{
    if (c == 0)
        return 1;
    return base * _pow(c - 1);
}

int binToDec(string str)
{
    int sum = 0;
    for (int i = str.length() - 1, c = 0; i >= 0; i--, c++)
        if (str[i] == '1')
            sum += _pow(c);
    return sum;
}

string toCharStr(int num)
{
    string st = "", res = "";
    while (num > 0)
    {
        num % 2 ? st.append("1") : st.append("0");
        num /= 2;
    }
    appendBits(st);
    reverse(st.begin(), st.end());
    for (int i = 0; i < st.length(); i += 8)
        res += char(binToDec((st.substr(i, 8))));
    return res;
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
    string encodedTreeL = toCharStr(tree.length());
    fs << encodedTreeL.length() << "=" << encodedTreeL << tree << res;
    fs.close();
}
string Dcd(string ec)
{
    string decoded = "";
    for (char c : ec)
    {
        std::bitset<8> b(c);
        decoded.append(b.to_string());
    }
    return decoded;
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

string appendBits(string &bits, int num)
{
    int mod = bits.length() % num;
    if (mod)
        for (int i = mod; i < num; i++)
            bits.append("0");
    return bits;
}

Fileinfo<int> getInfo(char ch, int t)
{
    return Fileinfo<int>(ch, t);
}

/*int binToDec(string str)
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
        //cout << "b:" << base << " d:" << dec_value << endl;
    }
    return dec_value;
}*/
/*
void doThat(string in)
{
    bitset<8> bset(in);
    unsigned long i = bset.to_ulong();
    unsigned char c = static_cast<unsigned char>(i);
    ecnd += c;
}*/