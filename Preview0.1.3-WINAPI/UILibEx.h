#pragma once
//-----------------------------------------------------分界线------------------------------------------------
#include "function.h"



#include "UIMain.h"

#include "Update.h"

#include "resource1.h"
//-----------------------------------------------------------------------------------------------------------


//-----------------------------------------
typedef struct tagww
{// 
    HWND hWnd11w;          // handle 

    LPCTSTR lpText11w;     // text 

    LPCTSTR lpCaption11w;  //  title 

    UINT uType11w;         // style 

} EDIT_PARAM1w;
//
BOOL CALLBACK DialogProc12w(HWND hwndDlg11w, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HBITMAP hBitmap;                  // 1 静态变量
    static HBITMAP hBitmap2;
    static HBITMAP hBitmap3;
    static HFONT hFont;//定义静态字体变量
    BITMAP         bitmap;
    static HWND close;
    HDC hdcMem = NULL;
    static int      bmWidth, bmHeight;       // 2 静态变量
    char txt[40];
    EDIT_PARAM1w* emmb = (EDIT_PARAM1w*)lParam;
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetWindowText(hwndDlg11w, emmb->lpCaption11w);
        SetWindowText(GetDlgItem(hwndDlg11w, IDC_STATIC90), emmb->lpText11w);
        //CloseBTN(hwndDlg11w,185,170, "关闭");
        return TRUE;
    case WM_PAINT:
    {
        HPEN hpen = CreatePen(PS_SOLID, 2, RGB(215, 122, 106));
        HPEN hpenOld = NULL;
        HDC hdc = NULL;
        HDC hdc2 = NULL;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwndDlg11w, &ps);
        HBRUSH br = CreateSolidBrush(RGB(60, 60, 60));
        FillRect(hdc, &ps.rcPaint, br);
        SelectObject(hdc, hpen);
        SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
        Rectangle(hdc, 0, 0, 174, 193);
        ReleaseDC(hwndDlg11w, hdc);//Over                                             // 12
        EndPaint(hwndDlg11w, &ps);
        DeleteObject(br);
        return TRUE;
    }
    case WM_CTLCOLORSTATIC:
    {
        if ((HWND)lParam == GetDlgItem(hwndDlg11w, IDC_STATICCMD)) //2
        {
            SetTextColor((HDC)wParam, RGB(78, 175, 106));
            SetBkMode((HDC)wParam, TRANSPARENT);
        }
        if ((HWND)lParam == GetDlgItem(hwndDlg11w, IDC_STATIC90)) //2
        {
            SetTextColor((HDC)wParam, RGB(210, 210, 210));
            SetBkColor((HDC)wParam, RGB(30, 30, 30));
        }
        if ((HWND)lParam == GetDlgItem(hwndDlg11w, IDC_STATIC91)) //2
        {
            SetTextColor((HDC)wParam, RGB(210, 210, 210));
            SetBkColor((HDC)wParam, RGB(30, 30, 30));
        }
        if ((HWND)lParam == GetDlgItem(hwndDlg11w, IDC_STATIC92)) //2
        {
            SetTextColor((HDC)wParam, RGB(210, 210, 210));
            SetBkColor((HDC)wParam, RGB(30, 30, 30));
        }
        return (INT_PTR)GetStockObject((NULL_BRUSH));//返回一个空画刷(必须)
    }
    case WM_LBUTTONDOWN:
    {
        if (DlgClose(hwndDlg11w, lParam) > 0)
        {
            DeleteObject(hBitmap);
            DeleteObject(hFont);
            EndDialog(hwndDlg11w, 0);
            break;
        }
        // 移动窗口 
        //SendMessage(hwndDlg1, WM_NCLBUTTONDOWN, HTCAPTION, 0);  //向窗口发送WM_NCLBUTTONDOWN消息，HTCAPTION 标题
        break;
    }
    case WM_ACTIVATE:
    {
        BOOL fActive;
        fActive = LOWORD(wParam);
        if (fActive == WA_ACTIVE)
        {
            break;
        }
        else
        {
            //--
            EndDialog(hwndDlg11w, 0);
            break;
        }
    }
    //--消息处理不知道放这里吗?
    case WM_COMMAND:
    {
        UINT uNotify = HIWORD(wParam);
        if (uNotify == BN_CLICKED)
        {
            switch (LOWORD(wParam))
            {
            case IDC_STATIC90:
            {
                genuuid();
                break;
            }
            case IDC_STATIC91:
            {
                bdmanifest();
                break;
            }
            case IDC_STATIC92:
            {
                buildres();
                break;
            }
            }
        }
    }
    case IDC_BUTT:
    {
        EndDialog(hwndDlg11w, 0);
        break;
    }
    case WM_CLOSE:
        EndDialog(hwndDlg11w, 0);
    }
    return FALSE;
}
//
int CmdlBox(
    HWND hWnd11w,          // handle 
    LPCTSTR lpText11w,     // text 
    LPCTSTR lpCaption11w,  // title 
    UINT uType11w          // style 
)
{
    EDIT_PARAM1w edit11w;
    edit11w.hWnd11w = hWnd11w;
    edit11w.lpText11w = lpText11w;
    edit11w.lpCaption11w = lpCaption11w;
    edit11w.uType11w = uType11w;
    DialogBoxParam((HINSTANCE)GetWindowLong(hWnd11w, GWL_HINSTANCE),
        MAKEINTRESOURCE(IDD_DIALOG5), NULL, DialogProc12w, (LPARAM)&edit11w);
    return -1;
}

#define     CMDLBOX CmdlBox
#include "UIdef.hpp"
//-----------------------------------------------------------------------------------------
typedef struct tagww1
{// 
    HWND hWnd11w;          // handle 

    LPCTSTR lpText11w;     // text 

    LPCTSTR lpCaption11w;  //  title 

    UINT uType11w;         // style 

} EDIT_PARAM1w1;
//
BOOL CALLBACK DialogProc12w1(HWND hwndDlg11w1, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HBITMAP hBitmap;                  // 1 静态变量
    static HBITMAP hBitmap2;
    static HBITMAP hBitmap3;
    HINSTANCE dlg_h = NULL;
    static HFONT hFont;//定义静态字体变量
    BITMAP         bitmap;
    static HWND close;
    HDC hdcMem = NULL;
    static int      bmWidth, bmHeight;       // 2 静态变量
    char txt[40];
    EDIT_PARAM1w* emmb = (EDIT_PARAM1w*)lParam;
    RECT rect;
    HBRUSH hbr = NULL;
    HPEN hpen = NULL;
    GetClientRect(hwndDlg11w1, &rect);
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetWindowText(hwndDlg11w1, emmb->lpCaption11w);
        //SetWindowText(GetDlgItem(hwndDlg11w1, IDC_MENUTXT0), emmb->lpText11w);
        //CloseBTN(hwndDlg11w,185,170, "关闭");
        return TRUE;
    case WM_PAINT:
    {
        HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 122, 204));
        HPEN hpenOld = NULL;
        HDC hdc = NULL;
        HDC hdc2 = NULL;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwndDlg11w1, &ps);
        HBRUSH br = CreateSolidBrush(RGB(60, 60, 60));
        FillRect(hdc, &ps.rcPaint, br);
        SelectObject(hdc, hpen);
        SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
        Rectangle(hdc, 0, 0, 117, 168);
        ReleaseDC(hwndDlg11w1, hdc);//Over                                             // 12
        EndPaint(hwndDlg11w1, &ps);
        DeleteObject(br);
        return TRUE;
    }
    case WM_CTLCOLORSTATIC:
    {
        if ((HWND)lParam == GetDlgItem(hwndDlg11w1, IDC_MENUTXT0)) //2
        {
            SetTextColor((HDC)wParam, RGB(78, 175, 106));
            SetBkColor((HDC)wParam, RGB(35, 35, 35));
        }
        if ((HWND)lParam == GetDlgItem(hwndDlg11w1, IDC_MENUTXT1)) //2
        {
            SetTextColor((HDC)wParam, RGB(78, 175, 106));
            SetBkColor((HDC)wParam, RGB(35, 35, 35));
        }
        return (INT_PTR)GetStockObject((NULL_BRUSH));//返回一个空画刷(必须)
    }
    case WM_LBUTTONDOWN:
    {
        if (DlgClose(hwndDlg11w1, lParam) > 0)
        {
            DeleteObject(hBitmap);
            DeleteObject(hFont);
            EndDialog(hwndDlg11w1, 0);
            break;
        }
        // 移动窗口 
        //SendMessage(hwndDlg1, WM_NCLBUTTONDOWN, HTCAPTION, 0);  //向窗口发送WM_NCLBUTTONDOWN消息，HTCAPTION 标题
        break;
    }
    case WM_ACTIVATE:
    {
        BOOL fActive;
        fActive = LOWORD(wParam);
        if (fActive == WA_ACTIVE)
        {
            break;
        }
        else
        {
            //--
            EndDialog(hwndDlg11w1, 0);
            break;
        }
    }
    //--消息处理不知道放这里吗?
    case WM_COMMAND:
    {
        UINT uNotify = HIWORD(wParam);
        if (uNotify == BN_CLICKED)
        {
            switch (LOWORD(wParam))
            {
            case IDC_MENUTXT0:
            {
                //PopBox(0, "正在获取更新...\n\n这可能需要一点时间qwq", "VersionSelector", 0);
                CreateWindow(L"#32770", L"正在获取更新...\n\n这可能需要一点时间qwq",
                    WS_POPUPWINDOW | WS_VISIBLE | WS_CAPTION,
                    rect.right + 175, rect.bottom + 130, 413, 30,
                    hwndDlg11w1,
                    0,
                    dlg_h,
                    FALSE);
                C_update();
                //TipBox(NULL, "当前版本:Pre-Beta0.0.1\n\n更新服务器:api", "CheckUpdate", NULL);
                break;
            }
            case IDC_MENUTXT1:
            {
                SettBox(NULL, NULL, L"设置", 0);
            }
            }
        }
    }
    case IDC_BUTT:
    {
        EndDialog(hwndDlg11w1, 0);
        break;
    }
    case WM_CLOSE:
        EndDialog(hwndDlg11w1, 0);
    }
    return FALSE;
}
//
int MenuBox(
    HWND hWnd11w,          // handle 
    LPCTSTR lpText11w,     // text 
    LPCTSTR lpCaption11w,  // title 
    UINT uType11w          // style 
)
{
    EDIT_PARAM1w edit11w;
    edit11w.hWnd11w = hWnd11w;
    edit11w.lpText11w = lpText11w;
    edit11w.lpCaption11w = lpCaption11w;
    edit11w.uType11w = uType11w;
    DialogBoxParam((HINSTANCE)GetWindowLong(hWnd11w, GWL_HINSTANCE),
        MAKEINTRESOURCE(IDD_DIALOG6), NULL, DialogProc12w1, (LPARAM)&edit11w);
    return -1;
}

#define     CMDLBOX CmdlBox