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

void toByte(string tree, string str, string path)
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
    ofstream fs(path, std::fstream::trunc | std::fstream::binary);
    if (!fs)
    {
        cout << "failed for writing";
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
    auto stream = ifstream(path, fstream::in | fstream::binary);
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
std::string redBin(const std::string &path)
{
    ifstream fin(path, ios::binary);
    ostringstream ostrm;
    ostrm << fin.rdbuf();
    return ostrm.str();
}
string readFile2(const string &path)
{
    ifstream ifs(path.c_str(), ios::in | ios::binary | ios::ate);
    ifstream::pos_type fs = ifs.tellg();
    if (fs < 0)
        return string();
    ifs.seekg(0, ios::beg);
    vector<char> bytes(fs);
    ifs.read(&bytes[0], fs);
    return string(&bytes[0], fs);
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
void writeFile(string path, string data)
{
    ofstream fs(path, fstream::trunc | fstream::binary);
    if (!fs)
    {
        cout << "failed for writing";
        exit(EXIT_FAILURE);
    }
    fs << data;
    fs.close();
}

/*for (char s : decoded)
    {
        temp.push_back(s);
        for (int i = 0; i < size; i++)
            if (hf[i].coded() == temp)
            {
                jk.push_back(hf[i].getSymbol());
                temp = "";
                break;
            }
    }*/

/*for (const char s : fl)
        for (int i = 0; i < size; i++)
            if (hf[i].findSymbol(s))
            {
                bits.append(hf[i].coded());
                break;
            }*/

/*for (const char s : fl)
        bits.append(ls->last().retrieve()->getCode(s));*/

/*for (char s : decoded)
    {
        temp += s;
        if (tree->_getSymbol(temp))
        {
            fl += tree->_symbol();
            temp = "";
        }
    }*/