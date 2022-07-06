#include "basewindow.h"
class MainWindow : public BaseWindow<MainWindow>
{
public:
    LPCSTR ClassName() const { return "Sample Window class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    BOOL HandleDialog(UINT uMsg, WPARAM wParam);
    void openFileDialog();
};