#include "mainwindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MainWindow win;
    if (!win.Create("Huffman compression utility", WS_OVERLAPPEDWINDOW))
        return 0;
    ShowWindow(win.Window(), nCmdShow);
    MSG msg = {};
    HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_MENU_ACC));
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(win.Window(), hAccel, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return 0;
}