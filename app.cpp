#include "mainwindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MainWindow win;
    if (!win.Create("Learn to Program Windows", WS_OVERLAPPEDWINDOW))
        return 0;
    ShowWindow(win.Window(), nCmdShow);
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}