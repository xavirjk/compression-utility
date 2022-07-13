#define NTDDI_VERSION 0x0A000006 //NTDDI_WIN10_RS5
#define _WIN32_WINNT 0x0A00      // _WIN32_WINNT_WIN10, the _WIN32_WINNT macro must also be defined when defining NTDDI_VERSION
#define FFS_HH 100
#include "mainwindow.h"
#include <shobjidl.h>
#include "string.h"
#include <mbstring.h>

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LOGFONT lf;
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_CREATE:
    {
        HFONT hFont;
        GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
        hFstrong = CreateFont(19, lf.lfWidth, lf.lfEscapement, lf.lfOrientation, 600, lf.lfItalic, lf.lfUnderline,
                              lf.lfStrikeOut, lf.lfCharSet, lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality, lf.lfPitchAndFamily, "Times NewRoman");
        CreateWindow("BUTTON", "", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 550, 20, 10, 400, m_hwnd, (HMENU)IDC_SEP, GetModuleHandle(NULL), NULL);
        HWND fText1 = CreateWindow("STATIC", "File Open", WS_VISIBLE | WS_CHILD | SS_RIGHT, 580, 40, 80, 30, m_hwnd, (HMENU)IDC_TXT0, GetModuleHandle(NULL), NULL);
        SendMessage(fText1, WM_SETFONT, WPARAM(hFstrong), MAKELPARAM(FALSE, 0));
        HWND fText2 = CreateWindow("STATIC", "CTRL + O", WS_VISIBLE | WS_CHILD | SS_LEFT, 670, 40, 100, 30, m_hwnd, (HMENU)IDC_TXT0, GetModuleHandle(NULL), NULL);
        SendMessage(fText2, WM_SETFONT, WPARAM(hFstrong), MAKELPARAM(FALSE, 0));
    }
        return 0;
    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT)lParam;
        SetTextColor(lpDIS->hDC, RGB(255, 255, 255));
        SetBkMode(lpDIS->hDC, TRANSPARENT);
        SelectObject(lpDIS->hDC, GetStockObject(DC_BRUSH));
        if (wParam == 504)
        {
            SetDCBrushColor(lpDIS->hDC, RGB(130, 130, 130));
            RoundRect(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top, lpDIS->rcItem.right, lpDIS->rcItem.bottom, 5, 5);
            DrawText(lpDIS->hDC, "Start Compression", -1, &lpDIS->rcItem, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            return TRUE;
        }
        else if (wParam == IDC_SEP)
        {
            SetDCBrushColor(lpDIS->hDC, RGB(50, 50, 50));
            RoundRect(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top, lpDIS->rcItem.right, lpDIS->rcItem.bottom, 5, 5);
            return TRUE;
        }
        break;
    }
    case WM_SIZE:
    {
        HWND hEdit;
        RECT rcClient;
        GetClientRect(m_hwnd, &rcClient);
        SetWindowPos(GetDlgItem(m_hwnd, IDC_MAIN_EDIT), NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(m_hwnd, IDC_GRPBUTTONS), NULL, 10, 10, rcClient.right - 300, rcClient.top + 100, SWP_NOZORDER);
    }
        return 0;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdc = (HDC)wParam;
        bool tt = wParam == 505;
        SetTextColor(hdc, RGB(0, 0, 0));
        SetBkMode(hdc, OPAQUE);
        return (INT_PTR)GetStockObject(HOLLOW_BRUSH);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(m_hwnd, &ps);
    }
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case FFS_HH:
        {
            HFONT hFont;
            GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
            hFont = CreateFont(16, lf.lfWidth, lf.lfEscapement, lf.lfOrientation, lf.lfWeight, lf.lfItalic, lf.lfUnderline,
                               lf.lfStrikeOut, lf.lfCharSet, lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality, lf.lfPitchAndFamily, "Times NewRoman");
            ShowWindow(GetDlgItem(m_hwnd, IDC_MAIN_EDIT), SW_HIDE);
            HWND hGrpButton;

            hGrpButton = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Select Process Mode:", WS_VISIBLE | WS_CHILD | WS_EX_TRANSPARENT | BS_GROUPBOX, 10, 10, 500, 100, m_hwnd, (HMENU)IDC_GRPBUTTONS, GetModuleHandle(NULL), NULL);
            SendMessage(hGrpButton, WM_SETFONT, WPARAM(hFont), TRUE);
            HWND rb1 = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Huffman encoding", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 30, 50, 200, 20, m_hwnd, (HMENU)IDC_CHK1, GetModuleHandle(NULL), NULL);
            SendMessage(rb1, WM_SETFONT, WPARAM(hFont), TRUE);
            HWND rb2 = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Canonize Huffman", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 250, 50, 200, 20, m_hwnd, (HMENU)IDC_CHK2, GetModuleHandle(NULL), NULL);
            SendMessage(rb2, WM_SETFONT, WPARAM(hFont), TRUE);
            HWND fText = CreateWindow("STATIC", nstring, WS_VISIBLE | WS_CHILD | SS_LEFT, 10, 150, 500, 30, m_hwnd, (HMENU)IDC_FLTXT, GetModuleHandle(NULL), NULL);
            SendMessage(fText, WM_SETFONT, WPARAM(hFont), MAKELPARAM(FALSE, 0));
            HWND ft = CreateWindow("BUTTON", "", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 10, 200, 150, 40, m_hwnd, (HMENU)IDC_BTNCMP, GetModuleHandle(NULL), NULL);
            SendMessage(ft, WM_SETFONT, WPARAM(hFont), TRUE);
            HWND fText1 = CreateWindow("STATIC", "Huffman", WS_VISIBLE | WS_CHILD | SS_RIGHT, 580, 80, 80, 30, m_hwnd, (HMENU)IDC_TXT0, GetModuleHandle(NULL), NULL);
            SendMessage(fText1, WM_SETFONT, WPARAM(hFstrong), MAKELPARAM(FALSE, 0));
            HWND fText2 = CreateWindow("STATIC", "CTRL + H", WS_VISIBLE | WS_CHILD | SS_LEFT, 670, 80, 100, 30, m_hwnd, (HMENU)IDC_TXT0, GetModuleHandle(NULL), NULL);
            SendMessage(fText2, WM_SETFONT, WPARAM(hFstrong), MAKELPARAM(FALSE, 0));
            HWND fText3 = CreateWindow("STATIC", "Canonize", WS_VISIBLE | WS_CHILD | SS_RIGHT, 580, 120, 80, 30, m_hwnd, (HMENU)IDC_TXT0, GetModuleHandle(NULL), NULL);
            SendMessage(fText3, WM_SETFONT, WPARAM(hFstrong), MAKELPARAM(FALSE, 0));
            HWND fText4 = CreateWindow("STATIC", "CTRL + N", WS_VISIBLE | WS_CHILD | SS_LEFT, 670, 120, 100, 30, m_hwnd, (HMENU)IDC_TXT0, GetModuleHandle(NULL), NULL);
            SendMessage(fText4, WM_SETFONT, WPARAM(hFstrong), MAKELPARAM(FALSE, 0));
            break;
        }
        case IDC_BTNCMP:
            root->compression(canonize);
            break;
        case IDC_CHK1:
            canonize = false;
            break;
        case IDC_CHK2:
            canonize = true;
            break;
        case ID_FILE_EXIT:
            PostMessage(m_hwnd, WM_CLOSE, 0, 0);
            break;
        case ID_STUFF_GO:
            break;
        case ID_FILE_OPEN:
            openFileDialog();
            break;
        case ID_FILE_CLOSE:
            break;
        case ID_HELP:
            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), m_hwnd, (DLGPROC)AboutDlgProc);
            break;
        }
    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}

BOOL MainWindow::HandleDialog(UINT uMsg, WPARAM wParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(m_hwnd, IDOK);
            break;
        case IDCANCEL:
            EndDialog(m_hwnd, IDCANCEL);
            break;
        }
        break;
    default:
        return FALSE;
    }
    return TRUE;
}
void MainWindow::openFileDialog()
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
                                          COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog *pFileOpen;
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                              IID_IFileOpenDialog, reinterpret_cast<void **>(&pFileOpen));
        if (SUCCEEDED(hr))
        {
            hr = pFileOpen->Show(NULL);
            if (SUCCEEDED(hr))
            {
                IShellItem *pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    if (SUCCEEDED(hr))
                    {
                        size_t origSize = wcslen(pszFilePath) + 1;
                        size_t converted = 0;
                        char strConcat[] = "";
                        size_t strConcatSize = (strlen(strConcat) + 1) * 2;
                        const size_t newSize = origSize * 2;
                        nstring = new char[newSize + strConcatSize];
                        wcstombs_s(&converted, nstring, newSize, pszFilePath, _TRUNCATE);
                        _mbscat_s((unsigned char *)nstring, newSize + strConcatSize, (unsigned char *)strConcat);
                        delete[] nstring;
                        root = new CMPDCP(nstring);
                        CoTaskMemFree(pszFilePath);
                        string ss = nstring, ext = ss.substr(ss.find_last_of(".") + 1);
                        if (ext == "huf" || ext == "cnz")
                            root->decompression(ext);
                        else
                            SendMessage(m_hwnd, WM_COMMAND, (WPARAM)FFS_HH, 0);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }
}