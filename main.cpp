#include <string>
#include "binarysearchtree.h"
int main(int argc, char *argv[])
{
    string fl = "Prove star Asf. Just for the love of the Game. Smart Challenges coming soon.";
    const char ch = 'T';
    int t = -1;
    BinarySearchTree<Fileinfo<int>> *bst = new BinarySearchTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
    BinarySearchTree<Fileinfo<int>> *huffman = new BinarySearchTree<Fileinfo<int>>(*bst);
    for (const char s : fl)
    {
        if (bst->findSymbol(s))
            continue;
        int frequency = 0;
        for (char si : fl)
            if (si == s)
                frequency++;
        bst->insert(Fileinfo<int>(s, frequency));
    }
    bst->printTree();
    Fileinfo<int> MAX = bst->findMax();
    Fileinfo<int> MIN = bst->findMin();
    cout << " Min appearance " << MIN.symbol << ":" << MIN.frequency << endl;
    cout << " Max appearance " << MAX.symbol << ":" << MAX.frequency << endl;
    ;
    /*while (!bst->isEmpty())
    {
        Fileinfo<int> f1, f2;
        f1 = bst->findMin();
        bst->remove(f1);
        f2 = bst->findMin();
        bst->remove(f2);
        int total = f1.frequency + f2.frequency;
        huffman->insert(Fileinfo<int>(ch, total));
        huffman->insert(f1);
        huffman->insert(f2);
    }*/

    return 0;
}