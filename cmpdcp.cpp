#include "cmpdcp.h"
#include "bits/stdc++.h"
#include <bitset>
CMPDCP::CMPDCP(const string &fn) : path(fn)
{
    ls = new List<BTree<Fileinfo<int>>>();
    t = -1;
}
CMPDCP::~CMPDCP() {}
void CMPDCP::compression()
{
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
    string newPath = path.substr(0, path.find_last_of(".")) + ".huf";
    ofstream out(newPath, ios::out | ios::binary);
    file_extension = path.substr(path.find_last_of("."));
    writeHead(out);
    writeBody(out);
    cout << "**finished compression**" << endl;
}
void CMPDCP::decompression()
{
    cout << "**init decompression**" << endl;
    tree = new BTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
    fl = readFile(path);
    start = 0;
    readHead();
    string filePath = path.substr(0, path.find_last_of(".")) + file_extension;
    ofstream out(filePath, ios::out | ios::binary);
    readBody(out);
    cout << "**completed**" << endl;
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

    hf = ls->last().retrieve()->huffman(size, false);
}

string CMPDCP::binary_string(int n)
{
    string st = "", res = "";
    while (n > 0)
    {
        n % 2 ? st += "1" : st += "0";
        n /= 2;
    }
    appendBits(st);
    reverse(st.begin(), st.end());
    for (int i = 0; i < st.length(); i += 8)
        res += char(binToDec((st.substr(i, 8))));
    return res;
}
void CMPDCP::writeHead(ofstream &out)
{

    string tree = ls->last().retrieve()->getTree();
    string encoded_tree_len = binary_string(tree.size());
    uint8_t tree_len = (uint8_t)encoded_tree_len.size();
    out.write((char *)&tree_len, 1);

    out << encoded_tree_len;
    for (auto it : tree)
        out.write(&it, 1);

    uint8_t max_len = (uint8_t)hf[size - 1]._len();
    out.write((char *)&max_len, 1);

    file_extension.size() == path.size() ? file_extension = "" : file_extension;
    uint8_t size_of_ext = (uint8_t)file_extension.size();
    out.write((char *)&size_of_ext, 1);
    out << file_extension;
}

void CMPDCP::writeBody(ofstream &out)
{
    string bits = "";
    for (const char s : fl)
    {
        int index = findChar(s);
        for (int i = 0; i < hf[index].coded().size(); i++)
        {
            if (bits.size() == 8)
            {
                char c = binToDec(bits);
                out.write(&c, 1);
                bits = "";
            }
            bits += hf[index].coded()[i];
        }
    }
    appendBits(bits);
    char c = binToDec(bits);
    out.write(&c, 1);
    out.flush();
    return;
}
void CMPDCP::readHead()
{
    char tree_len = fl[start];
    string _length = fl.substr(1, tree_len);

    int tree_size = binToDec(Dcd(_length));
    string _tree = fl.substr(1 + _length.size(), tree_size);

    char size_of_ext = fl[tree_size + 2 + _length.size()];
    file_extension = fl.substr(tree_size + 3 + _length.size(), size_of_ext);

    start = tree_size + 3 + _length.size() + size_of_ext;
    tree->mapTree(_tree);
}
void CMPDCP::readBody(ofstream &out)
{
    tree->_rcurrentNode();
    for (auto it : fl.substr(start))
    {
        std::bitset<8> b(it);
        int bitcount = 0;
        while (bitcount < 8)
        {
            if (tree->atLeaf())
            {
                out << tree->currentNode->element.symbol;
                tree->_rcurrentNode();
                bits = "";
                bits += b.to_string()[bitcount];
            }
            else
                bits += b.to_string()[bitcount];
            if (bits.back() == '1')
                tree->currentNode = tree->currentNode->right;
            else
                tree->currentNode = tree->currentNode->left;
            bitcount++;
        }
    }
    out.close();
}
string CMPDCP::Dcd(string c)
{
    string decoded = "";
    for (auto it : c)
    {
        std::bitset<8> b(it);
        decoded += b.to_string();
    }
    return decoded;
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
string CMPDCP::appendBits(string &bits)
{
    int mod = bits.length() % 8;
    if (mod)
        for (int i = mod; i < 8; i++)
            bits += "0";
    return bits;
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
    stream.close();
    return out;
}