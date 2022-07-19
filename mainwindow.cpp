#define NTDDI_VERSION 0x0A000006 //NTDDI_WIN10_RS5
#define _WIN32_WINNT 0x0A00      // _WIN32_WINNT_WIN10, the _WIN32_WINNT macro must also be defined when defining NTDDI_VERSION
#define FFS_HH 100
#include "mainwindow.h"
#include <shobjidl.h>
#include <mbstring.h>

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LOGFONT lf;
    RECT rcCl;
    GetClientRect(m_hwnd, &rcCl);
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_CREATE:
    {
        r_view = HOME;
        PostMessage(m_hwnd, WM_DRAW_MAIN, 0, 0);
    }

        return 0;
    case WM_DRAW_MAIN:
    {
        HFONT hFont;
        GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
        hFstrong = CreateFont(19, lf.lfWidth, lf.lfEscapement, lf.lfOrientation, 600, lf.lfItalic, lf.lfUnderline,
                              lf.lfStrikeOut, lf.lfCharSet, lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality, lf.lfPitchAndFamily, "Times NewRoman");
        CreateWindow("BUTTON", "", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, rcCl.right - 230, rcCl.top + 20, 10, rcCl.bottom - 50, m_hwnd, (HMENU)IDC_SEP, GetModuleHandle(NULL), NULL);
        HWND fText1 = CreateWindow("STATIC", "File Open", WS_VISIBLE | WS_CHILD | SS_RIGHT, rcCl.right - 200, 40, 100, 30, m_hwnd, (HMENU)IDC_TXT0, GetModuleHandle(NULL), NULL);
        SendMessage(fText1, WM_SETFONT, WPARAM(hFstrong), MAKELPARAM(FALSE, 0));
        HWND fText2 = CreateWindow("STATIC", "CTRL + O", WS_VISIBLE | WS_CHILD | SS_LEFT, rcCl.right - 90, 40, 100, 30, m_hwnd, (HMENU)IDC_TXT1, GetModuleHandle(NULL), NULL);
        SendMessage(fText2, WM_SETFONT, WPARAM(hFstrong), MAKELPARAM(FALSE, 0));
    }
        return 0;
    case WM_TIMER:
    {
        if (wParam == IDC_STATUS_TIMER)
            PostMessage(m_hwnd, WO_KILL_STATUS, 0, 0);
        else
            SendMessage(hProgress, PBM_STEPIT, 0, 0);
        break;
    }

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
        else if (wParam == IDC_BTNDCP)
        {
            SetDCBrushColor(lpDIS->hDC, RGB(130, 130, 130));
            RoundRect(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top, lpDIS->rcItem.right, lpDIS->rcItem.bottom, 5, 5);
            DrawText(lpDIS->hDC, "Decompress File", -1, &lpDIS->rcItem, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            return TRUE;
        }
        else if (wParam == IDC_STATUSBAR)
        {
            SetTextColor(lpDIS->hDC, RGB(55, 153, 55));
            SetDCBrushColor(lpDIS->hDC, RGB(240, 177, 95));
            RoundRect(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top, lpDIS->rcItem.right, lpDIS->rcItem.bottom, 5, 5);
            DrawText(lpDIS->hDC, root->statusMessage, -1, &lpDIS->rcItem, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
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
    case WM_DRAW_STATUSBAR:
    {
        statusBar = CreateWindow("BUTTON", "", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, rcCl.left + 30, rcCl.bottom - 90, rcCl.right - 300, 20, m_hwnd, (HMENU)IDC_STATUSBAR, GetModuleHandle(NULL), NULL);
        SendMessage(statusBar, WM_SETFONT, WPARAM(hFstrong), TRUE);
        SetTimer(m_hwnd, IDC_STATUS_TIMER, 2000, NULL);
        break;
    }
    case WM_SIZE:
    {
        HWND hEdit;
        SetWindowPos(GetDlgItem(m_hwnd, IDC_SEP), NULL, rcCl.right - 230, rcCl.top + 20, 10, rcCl.bottom - 50, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(m_hwnd, IDC_TXT0), NULL, rcCl.right - 200, 40, 100, 30, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(m_hwnd, IDC_TXT1), NULL, rcCl.right - 90, 40, 100, 30, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(m_hwnd, IDC_TXT2), NULL, rcCl.right - 200, 80, 100, 30, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(m_hwnd, IDC_TXT3), NULL, rcCl.right - 90, 80, 100, 30, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(m_hwnd, IDC_TXT4), NULL, rcCl.right - 200, 120, 100, 30, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(m_hwnd, IDC_TXT5), NULL, rcCl.right - 90, 120, 100, 30, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(m_hwnd, IDC_PROGRESS), NULL, rcCl.left + 30, rcCl.bottom - 50, rcCl.right - 300, 20, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(m_hwnd, IDC_STATUSBAR), NULL, rcCl.left + 30, rcCl.bottom - 90, rcCl.right - 300, 20, SWP_NOZORDER);
    }
        return 0;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdc = (HDC)wParam;
        bool tt = wParam == 505;
        SetTextColor(hdc, RGB(0, 0, 0));
        SetBkMode(hdc, TRANSPARENT);
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
    case WO_KILL_PR:
    {
        KillTimer(m_hwnd, IDC_TIMER);
        DestroyWindow(hProgress);
        operation_in_progress = false;
        PostMessage(m_hwnd, WM_DRAW_STATUSBAR, 0, 0);
        break;
    }
    case WO_KILL_STATUS:
    {
        KillTimer(m_hwnd, IDC_STATUS_TIMER);
        DestroyWindow(statusBar);
        break;
    }
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case FFS_HH:
        {
            r_view = OPR;
            EnumChildWindows(m_hwnd, DestroyChild, 0);
            PostMessage(m_hwnd, WM_DRAW_MAIN, 0, 0);
            root = new CMPDCP(nstring);
            HFONT hFont;

            GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
            hFont = CreateFont(17, lf.lfWidth, lf.lfEscapement, lf.lfOrientation, 500, lf.lfItalic, lf.lfUnderline,
                               lf.lfStrikeOut, lf.lfCharSet, lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality, lf.lfPitchAndFamily, "Times NewRoman");
            ShowWindow(GetDlgItem(m_hwnd, IDC_MAIN_EDIT), SW_HIDE);
            HWND fText = CreateWindow("STATIC", nstring, WS_VISIBLE | WS_CHILD | SS_LEFT, 10, 40, 500, 30, m_hwnd, (HMENU)IDC_FLTXT, GetModuleHandle(NULL), NULL);
            SendMessage(fText, WM_SETFONT, WPARAM(hFont), MAKELPARAM(FALSE, 0));
            HWND ft = CreateWindow("BUTTON", "", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 10, 100, 150, 40, m_hwnd, (HMENU)IDC_BTNCMP, GetModuleHandle(NULL), NULL);
            SendMessage(ft, WM_SETFONT, WPARAM(hFont), TRUE);
            HWND fText1 = CreateWindow("STATIC", "Compress", WS_VISIBLE | WS_CHILD | SS_RIGHT, rcCl.right - 200, 80, 100, 30, m_hwnd, (HMENU)IDC_TXT2, GetModuleHandle(NULL), NULL);
            SendMessage(fText1, WM_SETFONT, WPARAM(hFstrong), MAKELPARAM(FALSE, 0));
            HWND fText2 = CreateWindow("STATIC", "CTRL + C", WS_VISIBLE | WS_CHILD | SS_LEFT, rcCl.right - 90, 80, 100, 30, m_hwnd, (HMENU)IDC_TXT3, GetModuleHandle(NULL), NULL);
            SendMessage(fText2, WM_SETFONT, WPARAM(hFstrong), MAKELPARAM(FALSE, 0));
            std::string ss = nstring;
            fl_ext = ss.substr(ss.find_last_of(".") + 1);
            if (fl_ext == "huf")
            {
                HWND Bt2 = CreateWindow("BUTTON", "", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 300, 100, 150, 40, m_hwnd, (HMENU)IDC_BTNDCP, GetModuleHandle(NULL), NULL);
                SendMessage(Bt2, WM_SETFONT, WPARAM(hFont), TRUE);
                HWND fText3 = CreateWindow("STATIC", "Decompress", WS_VISIBLE | WS_CHILD | SS_RIGHT, rcCl.right - 200, 120, 100, 30, m_hwnd, (HMENU)IDC_TXT4, GetModuleHandle(NULL), NULL);
                SendMessage(fText3, WM_SETFONT, WPARAM(hFstrong), MAKELPARAM(FALSE, 0));
                HWND fText4 = CreateWindow("STATIC", "CTRL + D", WS_VISIBLE | WS_CHILD | SS_LEFT, rcCl.right - 90, 120, 100, 30, m_hwnd, (HMENU)IDC_TXT5, GetModuleHandle(NULL), NULL);
                SendMessage(fText4, WM_SETFONT, WPARAM(hFstrong), MAKELPARAM(FALSE, 0));
            }
            break;
        }
        case IDC_BTNCMP:
            operation();
            break;
        case IDC_BTNDCP:
            operation(false);
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
                        CoTaskMemFree(pszFilePath);
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

void MainWindow::showProgress()
{
    RECT rcCl;
    GetClientRect(m_hwnd, &rcCl);
    hProgress = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE, rcCl.left + 30, rcCl.bottom - 50, rcCl.right - 300, 20, m_hwnd, (HMENU)IDC_PROGRESS, GetModuleHandle(NULL), NULL);
    SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 60000 / 2048));
    SendMessage(hProgress, PBM_SETSTEP, (WPARAM)1, 0);
    SetTimer(m_hwnd, IDC_TIMER, 1000, NULL);
}
void MainWindow::operation(bool cMode)
{
    if (r_view == HOME || (cMode == false && fl_ext != "huf") || operation_in_progress)
        return;
    showProgress();
    DWORD id2;
    struct Data *tData = (struct Data *)malloc(sizeof(*tData));
    tData->root = root;
    tData->hWnd = m_hwnd;
    tData->cMode = cMode;
    operation_in_progress = true;
    CreateThread(0, 0, threadFunc, (LPVOID)tData, 0, &id2);
}
DWORD MainWindow::Threadstart(LPVOID Param)
{
    struct Data *tData = (struct Data *)Param;
    if (tData->cMode)
        tData->root->compression();
    else
        tData->root->decompression();
    PostMessage(tData->hWnd, WO_KILL_PR, 0, 0);
    return 1;
}
//CreateThread(0, 0, threadFunc, (LPVOID)m_hwnd, 0, &id2);