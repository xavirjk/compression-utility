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
    appendBits(bits);
    std::ostream &os = std::cout;
    toByte(ls->last().retrieve()->getTree(), bits);
    cout << "bits :" << bits << endl;
}
void CMPDCP::decompression()
{
    BinarySearchTree<Fileinfo<int>> *bst = new BinarySearchTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
    cout << "initializing decompression" << endl;
    string sc = readFile("E:\\qt-rec\\413_test\\output.txt");
    const string tLen = sc.substr(0, sc.find_first_of('='));
    int l = stoi(tLen);
    int start = binToDec(Dcd(sc.substr(sc.find_first_of('=') + 1, l)));
    int init = tLen.length() + 1 + l;
    string tree = sc.substr(init, start);
    init += start;
    string codes = sc.substr(init, sc.length());
    bst->mapTree(tree);
    hf = bst->huffman();
    const int size = bst->len();
    for (int i = 0; i < size; i++)
        hf[i].print();
    cout << Dcd(codes);
}

void CMPDCP::createHuffmanTree()
{
    const int size = ls->size();
    bits = "";
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
    ls->printList(*ls);
    hf = ls->last().retrieve()->huffman(size);
    for (int i = 0; i < size; i++)
        bits.append(hf[i].coded());
}