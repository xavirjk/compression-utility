#include <string>
#include "list.h"
#include <fstream>
#include <bitset>

int binToDec(string str);
void toByte(string tree, string str);
string readFile(string path);
int main(int argc, char *argv[])
{
    //string fl = "Hello World";
    //string fl = "Smart star Asf. Just for the love of the Game. Smart Challenges coming soon for the better good.\n the present and the past all witheld by me\n Best of luck.\nSmart star Asf. Just for the love of the Game. Smart Challenges coming soon for the better good.\n the present and the past all witheld by me\n Best of luck, and Jah bless. Cookies are many";
    //string fl = "AAAAAABCCCCCCDDEEEEEBBBBBBBBBBCCCCCCCC";
    string fl = readFile("E:\\qt-rec\\413_test\\data.txt");
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
        ls->insert(bst, ls->last());
    }
    ls->printList(*ls);
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
    cout << "done" << endl;
    ls->printList(*ls);
    Huffman *hf = ls->last().retrieve()->huffman(size);
    string bits = "";
    for (int i = 0; i < size; i++)
        bits.append(hf[i].coded());
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
    return 0;
}
int binToDec(string str)
{
    string num = str;
    int dec_value = 0;
    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--)
    {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    return dec_value;
}
void toByte(string tree, string str)
{
    int N = int(str.size());
    if (N % 8 != 0)
        return;
    string res = "";
    for (int i = 0; i < N; i += 8)
    {
        int decimal_value = binToDec((str.substr(i, 8)));
        res += char(decimal_value);
    }
    fstream fs;
    fs.open("E:\\qt-rec\\413_test\\output.txt");
    if (!fs)
    {
        cout << "fopen() failed for writing";
        exit(EXIT_FAILURE);
    }
    std::ostream &os = std::cout;
    os << endl
       << tree << " " << res << endl;
    fs << tree << " " << res;
    fs.close();

    string sc = readFile("E:\\qt-rec\\413_test\\output.txt");
    os << "*****" << endl
       << sc << endl
       << "*****" << endl;
    cout << "*****" << endl
         << sc << endl
         << "*****" << endl;
}
string readFile(string path)
{
    constexpr auto readSize = size_t(4096);
    auto stream = ifstream(path.data());
    stream.exceptions(ios_base::badbit);
    auto out = string();
    auto buf = string(readSize, '\0');
    while (stream.read(&buf[0], readSize))
    {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}