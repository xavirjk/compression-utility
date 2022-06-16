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
    return 0;
}