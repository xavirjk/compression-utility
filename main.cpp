#include "cmpdcp.h"
int main(int argc, char *argv[])
{
    string validity = argc > 1 ? argv[1] : "";
    CMPDCP *tool = new CMPDCP();
    if (validity.empty() || validity == "c")
        tool->compression();
    else
        tool->decompression();
    return 0;
}
