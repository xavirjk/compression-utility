#include "cmpdcp.h"
#include <bitset>
CMPDCP::CMPDCP(const string &fn) : path(fn)
{
    ls = new List<BinarySearchTree<Fileinfo<int>>>();
    t = -1;
}
CMPDCP::~CMPDCP() {}
void CMPDCP::compression()
{
    fl = readFile(path);
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
    toByte(ls->last().retrieve()->getTree(), bits, path);
}
void CMPDCP::decompression()
{
    BinarySearchTree<Fileinfo<int>> *bst = new BinarySearchTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
    cout << "initializing decompression" << endl;
    fl = readFile(path);
    const string tLen = fl.substr(0, fl.find_first_of('='));
    int l = stoi(tLen);
    int start = binToDec(Dcd(fl.substr(fl.find_first_of('=') + 1, l)));
    int init = tLen.length() + 1 + l;
    string tree = fl.substr(init, start);
    init += start;
    string codes = fl.substr(init, fl.length());
    bst->mapTree(tree);
    hf = bst->huffman();
    const int size = bst->len();
    string decoded = Dcd(codes);
    string temp = "";
    string jk = "";
    for (char s : decoded)
    {
        temp.push_back(s);
        for (int i = 0; i < size; i++)
            if (hf[i].coded() == temp)
            {
                jk.push_back(hf[i].getSymbol());
                temp = "";
                break;
            }
    }
    writeFile(path, jk);
    cout << "**Completed**" << endl;
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
    //ls->printList(*ls);
    hf = ls->last().retrieve()->huffman(size);
    for (const char s : fl)
        for (int i = 0; i < size; i++)
            if (hf[i].findSymbol(s))
            {
                bits.append(hf[i].coded());
                break;
            }
}