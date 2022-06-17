#include <string>
#include "list.h"
int main(int argc, char *argv[])
{
    string fl = "Prove star Asf. Just for the love of the Game. Smart Challenges coming soon";
    const char ch = 'T';
    int t = -1;
    List<BinarySearchTree<Fileinfo<int>>> *ls = new List<BinarySearchTree<Fileinfo<int>>>();
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
        ls->insert(bst, ls->zeroth());
    }
    ls->printList(*ls);
    while (ls->size() > 1)
    {
        BinarySearchTree<Fileinfo<int>> *nT = new BinarySearchTree<Fileinfo<int>>(Fileinfo<int>(ch, t));
        ListItr<BinarySearchTree<Fileinfo<int>>> min = ls->findMin();
        ls->remove(min.retrieve());
        ListItr<BinarySearchTree<Fileinfo<int>>> min2 = ls->findMin();
        ls->remove(min2.retrieve());
        int f = min.retrieve()->getFrequency(min.retrieve()) + min2.retrieve()->getFrequency(min2.retrieve());
        nT->insert(Fileinfo<int>(ch, f));
        nT->insertLeft(min.retrieve());
        nT->insertRight(min2.retrieve());
        ls->insert(nT, ls->last());
        //use depth to get left or right element.left should be deeper than right
        break;
    }
    return 0;
}