#include "cmpdcp.h"
int main(int argc, char *argv[])
{
    string validity = argc > 2 ? argv[1] : "";
    if (validity.empty())
    {
        cout << "EXIT!! No valid arguments provided.\nmain.exe <c||d> <path>";
        return 0;
    }
    /**
     * pass the second argument as the path to the file
     */

    CMPDCP *tool = new CMPDCP(argv[2]);
    if (validity == "c")
        tool->compression(); //Compress the file
    else
        tool->decompression(); //Decompress the file
    return 0;
}
