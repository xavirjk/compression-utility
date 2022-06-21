#include <string>
#include "list.h"
int main(int argc, char *argv[])
{
    string fl = "Hello World";
    //string fl = "Smart star Asf. Just for the love of the Game. Smart Challenges coming soon for the better good";
    const char ch = 'T';
    int t = -1;
    List<BinarySearchTree<Fileinfo<int>>> *ls = new List<BinarySearchTree<Fileinfo<int>>>();
    BinarySearchTree<Fileinfo<int>> *pr = new BinarySearchTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
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
    ls->printList(*ls);
    while (ls->size() > 1)
    {
        BinarySearchTree<Fileinfo<int>> *nT = new BinarySearchTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
        ListItr<BinarySearchTree<Fileinfo<int>>> min = ls->findMin();
        ListItr<BinarySearchTree<Fileinfo<int>>> min2 = ls->findMin();
        int f = min.retrieve()->getFrequency(min.retrieve()) + min2.retrieve()->getFrequency(min2.retrieve());
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
    cout << "done" << endl;
    ls->printList(*ls);
    return 0;
}