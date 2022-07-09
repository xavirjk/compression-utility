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
    /**
     * Pass the file to get the frequency occurence of the characters 
     * and represent each char as a node.
     * Insert each specific node in a list. You can use  a priority ques instead.
    */
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
    appendBits(bits);                                     //Perform bit padding to a multiple of 8
    toByte(ls->last().retrieve()->getTree(), bits, path); //Save the file
}
void CMPDCP::decompression()
{
    BTree<Fileinfo<int>> *tree = new BTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
    cout << "initializing decompression" << endl;
    fl = readFile(path);
    //length of the tree which is encoded
    const string tLen = fl.substr(0, fl.find_first_of('='));
    //convert tree length from string to int
    int l = stoi(tLen);
    //decode the tree length to decimal equivalent
    int start = binToDec(Dcd(fl.substr(fl.find_first_of('=') + 1, l)));
    int init = tLen.length() + 1 + l;
    string _tree = fl.substr(init, start);
    init += start;
    string codes = fl.substr(init, fl.length());
    tree->mapTree(_tree); //Reconstruct huffman tree
    cout << "reco" << endl;
    const int size = tree->len();
    string decoded = Dcd(codes);
    string temp = "";
    fl = "";
    cout << "done 2" << endl;
    hf = tree->huffman();
    cout << "done 3" << endl;
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
    /*for (char s : decoded)
    {
        temp += s;
        if (tree->_getSymbol(temp))
        {
            fl += tree->_symbol();
            temp = "";
        }
    }*/
    cout << "done 4" << endl;
    writeFile(path, fl);
    cout << "**Completed**" << endl;
}

void CMPDCP::createHuffmanTree()
{
    /**
    * Each loop gets the 2 minimum nodes merges them into a tree and removes them from the list
    * This goes on until one tree remains which is the huffman tree.
    */
    const int size = ls->size();
    bits = "";
    while (ls->size() > 1)
    {
        BTree<Fileinfo<int>> *nT = new BTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
        ListItr<BTree<Fileinfo<int>>> min = ls->findMin();
        ListItr<BTree<Fileinfo<int>>> min2 = ls->findMin();
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
    //Print  the contents of the tree
    /**
     * get the path of each char as binary code, when moving to the left 
     * maintain a 0 and to the right a 1
     */
    hf = ls->last().retrieve()->huffman(size);
    /**
     * This is the second pass of the file translate each character in the file into its 
     * equivalent code
    */
    /*for (const char s : fl)
        bits.append(ls->last().retrieve()->getCode(s));*/
    for (const char s : fl)
        for (int i = 0; i < size; i++)
            if (hf[i].findSymbol(s))
            {
                bits.append(hf[i].coded());
                break;
            }
}