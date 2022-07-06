#define NTDDI_VERSION 0x0A000006 //NTDDI_WIN10_RS5
#define _WIN32_WINNT 0x0A00      // _WIN32_WINNT_WIN10, the _WIN32_WINNT macro must also be defined when defining NTDDI_VERSION
#define FFS_HH 100
#include "mainwindow.h"
#include <shobjidl.h>

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LOGFONT lf;
    switch (uMsg)
    {
    case WM_CLOSE:
        if (MessageBox(m_hwnd, "Really Quit?", "Applicaton", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(m_hwnd);
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_CREATE:
    {
        /*HFONT hfDefault;
        HWND hEdit;
        hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 0, 0, 100, 100, m_hwnd, (HMENU)IDC_MAIN_EDIT, GetModuleHandle(NULL), NULL);
        if (hEdit == NULL)
            MessageBox(m_hwnd, "Could not create Edit box", "Error", MB_OK | MB_ICONERROR);*/
        //hfDefault = GetStockObject(DEFAULT_GUI_FONT);
        //SendMessage(hEdit, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
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
        break;
    }
    case WM_SIZE:
    {
        HWND hEdit;
        RECT rcClient;
        GetClientRect(m_hwnd, &rcClient);
        SetWindowPos(GetDlgItem(m_hwnd, IDC_MAIN_EDIT), NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(m_hwnd, IDC_GRPBUTTONS), NULL, 10, 10, rcClient.right - 100, rcClient.top + 100, SWP_NOZORDER);
    }
        return 0;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdc = (HDC)wParam;
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

            hGrpButton = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Select Process Mode:", WS_VISIBLE | WS_CHILD | WS_EX_TRANSPARENT | BS_GROUPBOX, 10, 10, 600, 100, m_hwnd, (HMENU)IDC_GRPBUTTONS, GetModuleHandle(NULL), NULL);
            SendMessage(hGrpButton, WM_SETFONT, WPARAM(hFont), TRUE);
            HWND rb1 = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Huffman encoding", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 30, 50, 200, 20, m_hwnd, (HMENU)IDC_CHK1, GetModuleHandle(NULL), NULL);
            SendMessage(rb1, WM_SETFONT, WPARAM(hFont), TRUE);
            HWND rb2 = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Canonize Huffman", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 250, 50, 200, 20, m_hwnd, (HMENU)IDC_CHK2, GetModuleHandle(NULL), NULL);
            SendMessage(rb2, WM_SETFONT, WPARAM(hFont), TRUE);
            HWND fText = CreateWindow("STATIC", "C:\\Qt_proj.s\\ComputerVision\\repos\\skillset\\windows", WS_VISIBLE | WS_CHILD | SS_LEFT, 10, 150, 500, 30, m_hwnd, (HMENU)IDC_FLTXT, GetModuleHandle(NULL), NULL);
            SendMessage(fText, WM_SETFONT, WPARAM(hFont), MAKELPARAM(FALSE, 0));
            HWND ft = CreateWindow("BUTTON", "", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 10, 200, 150, 40, m_hwnd, (HMENU)IDC_BTNCMP, GetModuleHandle(NULL), NULL);
            SendMessage(ft, WM_SETFONT, WPARAM(hFont), TRUE);
            break;
        }
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
        {
            int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), m_hwnd, (DLGPROC)AboutDlgProc);
            if (ret == IDOK)
            {
                MessageBox(m_hwnd,
                           "Dialog exited with IDOK.", "Notice", MB_OK | MB_ICONINFORMATION);
            }
            else if (ret == IDCANCEL)
            {
                MessageBox(m_hwnd,
                           "Dialog exited with IDCANCEL.", "Notice", MB_OK | MB_ICONINFORMATION);
            }
            else if (ret == -1)
            {
                MessageBox(m_hwnd,
                           "Dialog Failed!", "Error", MB_OK | MB_ICONINFORMATION);
            }
        }
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
                        MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
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