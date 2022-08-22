#include <windows.h>
#include "resource.h"

template <class DERIVED_TYPE>
class BaseWindow
{
public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        DERIVED_TYPE *pThis = NULL;
        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT *pCreate = (CREATESTRUCT *)lParam;
            pThis = (DERIVED_TYPE *)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
            pThis->m_hwnd = hwnd;
        }
        else
            pThis = (DERIVED_TYPE *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (pThis)
        {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    static BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        DERIVED_TYPE *pThis = NULL;
        switch (uMsg)
        {
        case WM_INITDIALOG:
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
            case IDOK:
                EndDialog(hwnd, IDOK);
                break;
            case IDCANCEL:
                EndDialog(hwnd, IDCANCEL);
                break;
            }
            break;
        default:
            return FALSE;
        }
        return TRUE;
    }
    BaseWindow() : m_hwnd(NULL) {}
    BOOL Create(
        LPCSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = 800,
        int nHeight = 500,
        HWND hWndParent = 0,
        HMENU hMenu = 0)
    {
        WNDCLASS wc = {0};
        wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = ClassName();
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MY_ICON));
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.lpszMenuName = MAKEINTRESOURCE(IDR_MY_MENU);
        wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

        RegisterClass(&wc);

        m_hwnd = CreateWindowEx(dwExStyle, ClassName(), lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this);
        return m_hwnd ? TRUE : FALSE;
    }
    HWND Window() const { return m_hwnd; }

protected:
    virtual LPCSTR ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
    virtual BOOL HandleDialog(UINT uMsg, WPARAM wParam) = 0;
    virtual void openFileDialog() = 0;

    HWND m_hwnd, hProgress, statusBar;
    HFONT hFstrong;
};