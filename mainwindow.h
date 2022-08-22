#include "basewindow.h"
#include "cmpdcp.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
    static DWORD WINAPI threadFunc(LPVOID Param)
    {
        MainWindow *This = (MainWindow *)Param;
        return This->Threadstart(Param);
    }
    static BOOL CALLBACK DestroyChild(HWND hwnd, LPARAM lParam)
    {
        if (hwnd != NULL)
            DestroyWindow(hwnd);
        return TRUE;
    }
    LPCSTR ClassName() const { return "Sample Window class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    BOOL HandleDialog(UINT uMsg, WPARAM wParam);
    void openFileDialog();
    void showProgress();
    DWORD Threadstart(LPVOID Param);
    void operation(bool cMode = true);

private:
    CMPDCP *root;
    char *nstring;
    std::string fl_ext = "";
    enum VIEWS
    {
        HOME,
        OPR
    } r_view;
    const char *VIEWS_NAMES[2] = {"Homepage", "operation"};
    struct Data
    {
        CMPDCP *root;
        HWND hWnd;
        bool cMode;
    };
    bool operation_in_progress = false;
};