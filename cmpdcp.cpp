#include "cmpdcp.h"
#include <bitset>
CMPDCP::CMPDCP()
{
    ls = new List<BinarySearchTree<Fileinfo<int>>>();
    t = -1;
}
CMPDCP::~CMPDCP() {}
void CMPDCP::compression()
{
    fl = readFile("E:\\qt-rec\\413_test\\data.txt");
    for (const char s : fl)
    {
        BinarySearchTree<Fileinfo<int>> *bst = new BinarySearchTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
        if (ls->findSymbol(s))
            continue;
        int frequency = 0;
        for (char si : fl)
            if (si == s)
                frequency++;
        bst->insert(Fileinfo<int>(s, frequency));
        ls->insert(bst, ls->last());
    }
    createHuffmanTree();
    int mod = bits.length() % 8;
    if (mod)
        for (int i = mod; i < 8; i++)
            bits.append("0");
    std::ostream &os = std::cout;
    toByte(ls->last().retrieve()->getTree(), bits);
    bitset<8> bset(string("10110000"));
    unsigned long i = bset.to_ulong();
    unsigned char c = static_cast<unsigned char>(i);
    cout << "ss " << c << endl;
    std::bitset<8> b(c);
    os << "b is " << b << endl;
    cout << "fin" << endl;
}
void CMPDCP::decompression()
{
    cout << "initializing decompression" << endl;
}

void CMPDCP::createHuffmanTree()
{
    const int size = ls->size();
    while (ls->size() > 1)
    {
        BinarySearchTree<Fileinfo<int>> *nT = new BinarySearchTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
        ListItr<BinarySearchTree<Fileinfo<int>>> min = ls->findMin();
        ListItr<BinarySearchTree<Fileinfo<int>>> min2 = ls->findMin();
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
    Huffman *hf = ls->last().retrieve()->huffman(size);
    string bits = "";
    for (int i = 0; i < size; i++)
        bits.append(hf[i].coded());
}