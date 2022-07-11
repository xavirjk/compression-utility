#include "cmpdcp.h"
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
        BTree<Fileinfo<int>> *tree = new BTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
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
    appendBits(bits);
    string newPath = path.substr(0, path.find_last_of(".")) + ".huf";
    toByte(ls->last().retrieve()->getTree(), bits, newPath);
}
void CMPDCP::decompression()
{
    BTree<Fileinfo<int>> *tree = new BTree<Fileinfo<int>>(Fileinfo<int>(ch, t));

    fl = readFile(path);
    const string tLen = fl.substr(0, fl.find_first_of('='));
    int l = stoi(tLen);
    int start = binToDec(Dcd(fl.substr(fl.find_first_of('=') + 1, l)));
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
    cout << "**Completed**" << endl;
}

void CMPDCP::createHuffmanTree()
{
    const int size = ls->size();
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

    hf = ls->last().retrieve()->huffman(size);

    for (const char s : fl)
        for (int i = 0; i < size; i++)
            if (hf[i].findSymbol(s))
            {
                bits.append(hf[i].coded());
                break;
            }
}
