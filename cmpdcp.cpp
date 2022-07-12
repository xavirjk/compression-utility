#include "cmpdcp.h"
#include "sort.h"
#include "bits/stdc++.h"
#include <bitset>
#include <sstream>
using namespace MP::sort;
CMPDCP::CMPDCP(const string &fn) : path(fn)
{
    ls = new List<BTree<Fileinfo<int>>>();
    t = -1;
}
CMPDCP::~CMPDCP() {}
void CMPDCP::compression(bool canonize)
{
    _canonize = canonize;
    fl = readFile(path);

    for (const char s : fl)
    {
        tree = new BTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
        if (ls->findSymbol(s))
            continue;
        int frequency = 0;
        for (char si : fl)
            if (si == s)
                frequency++;
        tree->insert(Fileinfo<int>(s, frequency));
        ls->insert(tree, ls->last());
    }

    createHuffmanTree();
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
        string newPath = path.substr(0, path.find_last_of(".")) + ".cnz";
        ofstream out(newPath, ios::out | ios::binary);
        writeHead(out, path.substr(path.find_last_of(".") + 1));
        writeBody(out);
    }
    else
    {
        for (const char s : fl)
            for (int i = 0; i < size; i++)
                if (hf[i].findSymbol(s))
                {
                    bits.append(hf[i].coded());
                    break;
                }
        //appendBits(bits);
        //string newPath = path.substr(0, path.find_last_of(".")) + ".huf";
        //toByte(ls->last().retrieve()->getTree(), bits, newPath);
    }
}
void CMPDCP::decompression(string fileType)
{
    tree = new BTree<Fileinfo<int>>(Fileinfo<int>(ch, t));

    fl = readFile(path);
    if (fileType == "cnz")
    {
        start = 0;
        readHead();
        readBody();
    }
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
}

void CMPDCP::createHuffmanTree()
{
    size = ls->size();
    bits = "";

    while (ls->size() > 1)
    {
        BTree<Fileinfo<int>> *nT = new BTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
        ListItr<BTree<Fileinfo<int>>> min = ls->findMin(), min2 = ls->findMin();

        int f = min.retrieve()->getFrequency() + min2.retrieve()->getFrequency();

        nT->insert(Fileinfo<int>(ch, f));

        if (min.retrieve()->depth() < min2.retrieve()->depth())
        {
            nT->insertLeft(min2.retrieve());
            nT->insertRight(min.retrieve());
        }
        else
        {
            nT->insertRight(min2.retrieve());
            nT->insertLeft(min.retrieve());
        }

        ls->insert(nT, ls->last());
        ls->remove(min);
        ls->remove(min2);
    }

    hf = ls->last().retrieve()->huffman(size, _canonize);
}

void CMPDCP::canonizeHuffman()
{
    int current = 0, pbl = hf[0]._len();

    for (int i = 0; i < size; i++)
    {
        int shift_bits = hf[i]._len() - pbl;
        current = current << shift_bits;
        hf[i].canonicalCodes(binary_string(current, hf[i]._len()));
        ++current;
        pbl = hf[i]._len();
    }
}

string CMPDCP::binary_string(int n, int bit_size)
{
    string st = "", res = "";
    if (!n)
        st += "0";
    while (n > 0)
    {
        n % 2 ? st += "1" : st += "0";
        n /= 2;
    }
    reverse(st.begin(), st.end());
    return st;
}
void CMPDCP::writeHead(ofstream &out, string ext)
{

    uint8_t max_len = (uint8_t)hf[size - 1]._len();
    out.write((char *)&max_len, 1);

    unsigned long search_I = 0;
    for (int i = 1; i <= max_len; i++)
    {
        uint8_t _count = 0;
        while (search_I < size)
        {
            if (i == hf[search_I]._len())
            {
                _count++;
                search_I++;
            }
            else
                break;
        }
        out.write((char *)&_count, 1);
    }

    uint8_t num_of_chars = (uint8_t)size;
    out.write((char *)&num_of_chars, 1);
    for (int i = 0; i < size; i++)
    {
        char c = hf[i].getSymbol();
        out.write(&c, 1);
    }

    ext.size() == path.size() ? ext = "" : ext = ext;
    uint8_t size_of_ext = (uint8_t)ext.size();
    out.write((char *)&size_of_ext, 1);
    out << ext;
}

void CMPDCP::writeBody(ofstream &out)
{
    string bits = "";
    for (const char s : fl)
    {
        int index = findChar(s);
        for (int i = 0; i < hf[index]._len(); i++)
        {
            if (bits.length() == 8)
            {
                char c = binToDec(bits);
                out.write(&c, 1);
                bits = "";
            }
            bits += hf[index].coded()[i];
        }
    }
    appendBits(bits, out);
    out.flush();
    return;
}
void CMPDCP::readHead()
{
    cout << fl << endl;

    char max_len = fl[start];
    string _length = fl.substr(1, max_len);

    char num_of_chars = fl[max_len + 1];
    string symbols = fl.substr(max_len + 2, num_of_chars);

    char size_of_ext = fl[max_len + 2 + num_of_chars];
    string ext = fl.substr(max_len + 2 + num_of_chars + 1, size_of_ext);

    start = max_len + num_of_chars + size_of_ext + 3;
    int symbolsIndex = 0;

    int currCode = 0;

    int previousCode = -1;
    int previousLength = 0;
    tree->createRoot();
    for (int i = 0; i < (int)_length.size(); i++)
    {
        char n = _length[i];
        if (n)
        {
            for (int j = 0; j < n; j++)
            {
                char c = symbols[symbolsIndex];

                currCode = (previousCode + 1) << (i - previousLength);
                tree->canonized(binary_string(currCode, i + 1), c);
                symbolsIndex++;
                previousCode = currCode;
                previousLength = i;
            }
        }
    }
}
void CMPDCP::readBody()
{
    tree->print();
    cout << fl.substr(start) << endl;
}

int CMPDCP::findChar(char s)
{
    int i;
    for (i = 0; i < size; i++)
        if (hf[i].getSymbol() == s)
            break;
    return i;
}
int CMPDCP::binToDec(string str)
{
    int sum = 0;
    for (int i = str.length() - 1, c = 0; i >= 0; i--, c++)
        if (str[i] == '1')
            sum += _pow(c);
    return sum;
}
int CMPDCP::_pow(int c, int base)
{
    if (c == 0)
        return 1;
    return base * _pow(c - 1);
}
void CMPDCP::appendBits(string bits, ofstream &out)
{
    int mod = bits.length() % 8;
    if (!mod)
        return;
    for (int i = mod; i < 8; i++)
        bits += "0";
    char c = binToDec(bits);
    out.write(&c, 1);
}
string CMPDCP::readFile(string path)
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