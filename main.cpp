#include "cmpdcp.h"
int main(int argc, char *argv[])
{
    string validity = argc > 2 ? argv[1] : "";
    if (validity.empty())
    {
        cout << "EXIT!! No valid arguments provided.\nmain.exe <c||d> <path>";
        return 0;
    }
    CMPDCP *tool = new CMPDCP(argv[2]);
    if (validity == "c")
        tool->compression();
    else
        tool->decompression();
    return 0;
}
