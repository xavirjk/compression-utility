#include "utils.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include "bits/stdc++.h"
using namespace std;

Fileinfo<int> getInfo(char ch, int t)
{
    return Fileinfo<int>(ch, t);
}

/*int _pow(int c, int base)
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
}*/

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

/*string CMPDCP::Dcd(char c)
{
    string decoded = "";
    std::bitset<8> b(c);
    decoded.append(b.to_string());
    return decoded;
}*/
/*tree->print();
    cout << fl.substr(start) << endl;*/
/*ls->printList(*ls);
    if (canonize)
    {
        HeapSort *hp = new HeapSort();

        hp->heapSort(hf, size);
        for (int i = 0; i < size; i++)
        {
            int k;

            if (size == i + 1 || hf[i]._len() != hf[i + 1]._len())
                continue;

            for (k = i + 1; k < size; k++)
                if (hf[k]._len() != hf[i]._len())
                    break;

            hp->heapSort(hf, k - i, true, i);

            i += k - i - 1;
        }
        canonizeHuffman();
        cout << "canonized" << endl;
        string newPath = path.substr(0, path.find_last_of(".")) + ".cnz";
        ofstream out(newPath, ios::out | ios::binary);
        file_extension = path.substr(path.find_last_of("."));
        writeHead(out);
        writeBody(out);
    }*/
/*void CMPDCP::canonizeHuffman()
{
    int previousLength = 0;
    int currVal = 0;
    int canonicalLength = 0;
    for (int i = 0; i < size; i++)
    {
        char c = hf[i].getSymbol();
    }
    for (auto &it : codeLengthMap)
    {

        set<char> *charSet = it.second;
        canonicalLength += (it.first - previousLength);
        currVal = (currVal) << (it.first - previousLength);
        for (auto c : *charSet)
        {
            std::cout << c << ":" << canonicalLength << ":" << currVal << std::endl;
            canonicalCodeMap.insert({c, pair<int, int>{canonicalLength, currVal}});
            currVal += 1;
        }
        previousLength = it.first;
    }
    return canonicalCodeMap;
    int current = 0, pbl = hf[0]._len();

    for (int i = 0; i < size; i++)
    {
        int shift_bits = hf[i]._len() - pbl;
        current = current << shift_bits;
        //cout << hf[i].getSymbol() << ":" << current << endl;
        hf[i].canonicalCodes(binary_string(current, hf[i]._len()));
        ++current;
        pbl = hf[i]._len();
    }
}*/
/*
    for (const char s : fl)
        for (int i = 0; i < size; i++)
            if (hf[i].findSymbol(s))
            {
                bits.append(hf[i].coded());
                break;
            }*/
//appendBits(bits);
//string newPath = path.substr(0, path.find_last_of(".")) + ".huf";
//toByte(ls->last().retrieve()->getTree(), bits, newPath);
/*if (fileType == "cnz")
    {
        start = 0;
        readHead();
        //filePath = path.substr(0, path.find_last_of(".")) + file_extension;
        filePath = "E:\\qt-rec\\413_test\\gf.txt";
        ofstream out(filePath, ios::out | ios::binary);
        readBody(out);
        cout << endl;
        //tree->print();
        cout << "**completed**" << endl;
    }*/
//out.close();
/*bits = "";
    string decoded = "";
    int parsedBits = 8;
    tree->_rcurrentNode();
    for (char it : fl.substr(start))
    {
        std::bitset<8> b(it);
        decoded += b.to_string();
    }
    tree->print();
    cout << endl;
    cout << decoded << endl;
    for (char s : decoded)
    {
        if (tree->atLeaf())
        {
            cout << tree->currentNode->element.symbol;
            tree->_rcurrentNode();
        }
        if (s == '1')
            tree->currentNode = tree->currentNode->right;
        else
            tree->currentNode = tree->currentNode->left;
    }*/
/*for (auto it : fl.substr(start))
    {
        std::bitset<8> b(it);
        bits += b.to_string();
        cout << bits;
        for (int i = 8 - parsedBits; i < 8; i++)
        {
            if (tree->atLeaf())
            {
                out << tree->currentNode->element.symbol;
                parsedBits = i;
                tree->_rcurrentNode();
            }
            if (bits[i] == '1')
                tree->currentNode = tree->currentNode->right;
            else
                tree->currentNode = tree->currentNode->left;
        }
        bits = bits.substr(parsedBits);
    }*/
//out.close();
//const string tLen = fl.substr(0, fl.find_first_of('='));
//int l = stoi(tLen);
/*int start = binToDec(Dcd(fl.substr(fl.find_first_of('=') + 1, l)));
    int init = tLen.length() + 1 + l;

    string _tree = fl.substr(init, start);
    init += start;

    string codes = fl.substr(init, fl.length());

    tree->mapTree(_tree);

    const int size = tree->len();
    string decoded = Dcd(codes), temp = "";
    fl = "";

    hf = tree->huffman();

    for (char s : decoded)
    {
        temp.push_back(s);
        for (int i = 0; i < size; i++)
            if (hf[i].coded() == temp)
            {
                fl.push_back(hf[i].getSymbol());
                temp = "";
                break;
            }
    }

    writeFile(path, fl);
    cout << "**Completed**" << endl;*/