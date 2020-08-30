#pragma once
#include "TxtType.h"
#include "Colordef.h"
#pragma comment( lib, "Msimg32.lib" )
#pragma warning(disable:4996)
//-----------------------------------------------------------------------------------------------------------------------
#define MAX_LOADSTRING 100
#define IDB_MY_BUTTON     3100


#define IDC_CLOSE 10003

#define IDC_STATE 10004

#define IDC_BUTT 7845

#define IDC_MINIMIZE 12111

#define IDC_EDIT1 114514

#define CLOSEBTN 114513


//-------------------------------------------------------------------------------------------------------------------------
#include "framework.h"
#include "Resource.h"
#include <tchar.h>
#include <stdio.h>
#include <commctrl.h>
#include <sstream>
#include <atlconv.h>
//-----------------------------------------------------------------------------------------------------------------------
HINSTANCE b_hInstance;
//------------------------------------------------------------------------------------------------------------------------
int DlgClose(HWND hwndDlg, LPARAM lParam)
{
    POINT pt;
    wchar_t txt[80];
    pt.x = LOWORD(lParam);
    pt.y = HIWORD(lParam);
    wsprintf(txt, L"x=%d;y=%d\n", LOWORD(lParam), HIWORD(lParam));
    OutputDebugString(txt);
    RECT  rc = { 410, 5, 440, 25 };// 这是 bmp 在主窗口的位置 ！
    if (PtInRect(&rc, pt))
    {
        return WM_CLOSE;
    }
    return -1;
}
//------------------------------------------------------------------------------------------------------------------------
HWND g_bt1;
HWND g_bt2;
WNDPROC BToldProc;

typedef struct tagBTN
{// 
    HWND hWnd;          // handle of owner window
    BOOL x1; //默认是185
    BOOL x2; //默认是170
    LPWSTR in;
    UINT style;
} BTN_PARAM;
//
//
LRESULT CALLBACK BTProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{// 
    PAINTSTRUCT ps;
    HDC hdc = NULL;
    RECT rc;
    GetClientRect(hWnd, &rc);
    LOGFONT lf;
    HFONT hFont = 0;
    HBRUSH br;
    TCHAR txt[40];
    switch (Msg)
    {//
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        br = CreateSolidBrush(RGB(7, 130, 215));
        FillRect(hdc, &rc, br);
        GetWindowText(hWnd, txt, 40);
        SetTextColor(hdc, TEXTBLACK);
        SetBkMode(hdc, TRANSPARENT);
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, 18, 7, txt, wcslen(txt) /*&ps.rcPaint*//*DT_SINGLELINE | DT_CENTER | DT_VCENTER*/);
        //DrawText(hdc, txt, wcslen(txt), &ps.rcPaint, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        ReleaseDC(hWnd, hdc);
        UpdateWindow(hWnd);
        DeleteObject(br);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_MOUSEMOVE:
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_HOVER | TME_LEAVE;
        tme.dwHoverTime = 1;
        tme.hwndTrack = hWnd;
        BOOL boRet = _TrackMouseEvent(&tme);
    }break;
    case WM_MOUSELEAVE:
    {
        
        PAINTSTRUCT ps1;
        HBRUSH hbr = NULL;
        hdc = GetDC(hWnd);
        hbr = CreateSolidBrush(RGB(7,130,215));
        FillRect(hdc, &rc, hbr);
        GetWindowText(hWnd, txt, 40);
        SetTextColor(hdc, TEXTBLACK);
        SetBkMode(hdc, TRANSPARENT);
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, 18, 7, txt, wcslen(txt) /*&ps.rcPaint*//*DT_SINGLELINE | DT_CENTER | DT_VCENTER*/);
        //SetWindowText(hWnd, L"关闭");
        //SetWindowText(hWnd, L"关闭");
        ReleaseDC(hWnd, hdc);
        DeleteObject(hbr);
        OutputDebugStringA("Leave\n");
        break;
    }
    case WM_MOUSEHOVER:
    {
        HBRUSH hbr = NULL;
        hdc = GetDC(hWnd);
        hbr = CreateSolidBrush(RGB(99, 184, 255));
        SelectObject(hdc, hbr);
        FillRect(hdc, &rc, hbr);
        GetWindowText(hWnd, txt, 40);
        SetTextColor(hdc, TEXTBLACK);
        SetBkMode(hdc, TRANSPARENT);
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, 18, 7, txt, wcslen(txt) /*&ps.rcPaint*//*DT_SINGLELINE | DT_CENTER | DT_VCENTER*/);
        //SetWindowText(hWnd, L"关闭");
        ReleaseDC(hWnd, hdc);
        //SetWindowText(hWnd, L"[关闭]");
        DeleteObject(hbr);
        OutputDebugStringA("Over\n");
        break;
    }
    }
    //
    return CallWindowProc(BToldProc, hWnd, Msg, wParam, lParam);
}
//________________HWND 主窗口,__x1 x坐标,__x2 y坐标,L"按钮文字",从定义获取控件
//如果需要进行消息处理,case IDC_XX:
int Button(
    HWND hWnd,         // handle of owner window
    BOOL x1,
    BOOL x2,
    LPWSTR in,
    UINT style //从定义获取按钮控件依赖
)
{
    static HFONT hFont;
    BTN_PARAM btn;
    btn.hWnd = hWnd;
    btn.style = style;
    g_bt1 = CreateWindow(L"Button", in, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON|BS_TEXT | BS_OWNERDRAW,//默认按钮样式
        x1, x2, 70, 30, hWnd, (HMENU)style, b_hInstance, NULL);
    BToldProc = (WNDPROC)SetWindowLong(g_bt1, GWL_WNDPROC, (LONG)BTProc);
    return -1;
}
//---------------------------------------------------------------------------------------------------
typedef struct tagBTNX
{// 
    HWND hWnd;          // handle of owner window
    BOOL x1; //默认是185
    BOOL x2; //默认是170
    BOOL rcx1;
    BOOL rcy1;
    LPWSTR in;
    COLORREF crf;
    UINT style;
} BTN_PARAMX;
//
//
LRESULT CALLBACK BTProcX(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{// 
    PAINTSTRUCT ps;
    HDC hdc = NULL;
    RECT rc;
    GetClientRect(hWnd, &rc);
    LOGFONT lf;
    HFONT hFont = 0;
    HBRUSH br;
    TCHAR txt[40];
    switch (Msg)
    {//
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        br = CreateSolidBrush(LBLUE);
        //br = CreateSolidBrush(RGB(7, 130, 215));
        FillRect(hdc, &rc, br);
        GetWindowText(hWnd, txt, 40);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, TEXTBLACK);
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, 18, 7, txt, wcslen(txt) /*&ps.rcPaint*//*DT_SINGLELINE | DT_CENTER | DT_VCENTER*/);
        //DrawText(hdc, txt, wcslen(txt), &ps.rcPaint, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        ReleaseDC(hWnd, hdc);
        UpdateWindow(hWnd);
        DeleteObject(br);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_MOUSEMOVE:
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_HOVER | TME_LEAVE;
        tme.dwHoverTime = 1;
        tme.hwndTrack = hWnd;
        BOOL boRet = _TrackMouseEvent(&tme);
    }break;
    case WM_MOUSELEAVE:
    {

        PAINTSTRUCT ps1;
        HBRUSH hbr = NULL;
        hdc = GetDC(hWnd);
        hbr = CreateSolidBrush(LBLUE);
        SelectObject(hdc, hbr);
        FillRect(hdc, &rc, hbr);
        GetWindowText(hWnd, txt, 40);
        SetTextColor(hdc, TEXTBLACK);
        SetBkMode(hdc, TRANSPARENT);
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, 18, 7, txt, wcslen(txt) /*&ps.rcPaint*//*DT_SINGLELINE | DT_CENTER | DT_VCENTER*/);
        //SetWindowText(hWnd, L"关闭");
        ReleaseDC(hWnd, hdc);
        DeleteObject(hbr);
        OutputDebugStringA("Leave\n");
        break;
    }
    case WM_MOUSEHOVER:
    {
        HBRUSH hbr = NULL;
        hdc = GetDC(hWnd);
        hbr = CreateSolidBrush(RGB(99, 184, 255));
        SelectObject(hdc, hbr);
        FillRect(hdc, &rc, hbr);
        GetWindowText(hWnd, txt, 40);
        SetTextColor(hdc, TEXTBLACK);
        SetBkMode(hdc, TRANSPARENT);
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, 18, 7, txt, wcslen(txt) /*&ps.rcPaint*//*DT_SINGLELINE | DT_CENTER | DT_VCENTER*/);
        //SetWindowText(hWnd, L"关闭");
        ReleaseDC(hWnd, hdc);
        //SetWindowText(hWnd, L"[关闭]");
        DeleteObject(hbr);
        OutputDebugStringA("Over\n");
        break;
    }
    }
    //
    return CallWindowProc(BToldProc, hWnd, Msg, wParam, lParam);
}
//________________HWND 主窗口,__x1 x坐标,__x2 y坐标,[面积]L"按钮文字",从定义获取控件
//如果需要进行消息处理,case IDC_XX:
int ButtonEx(
    HWND hWnd,         // handle of owner window
    BOOL x1,
    BOOL x2,
    BOOL rcx1,
    BOOL rcy1,
    LPWSTR in,
    UINT style //从定义获取按钮控件依赖
)
{
    static HFONT hFont;
    BTN_PARAMX btn;
    btn.hWnd = hWnd;
    btn.style = style;
    g_bt1 = CreateWindow(L"Button", in, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,//默认按钮样式
        x1, x2, rcx1, rcy1, hWnd, (HMENU)style, b_hInstance, NULL);
    BToldProc = (WNDPROC)SetWindowLong(g_bt1, GWL_WNDPROC, (LONG)BTProcX);
    return -1;
}
//---------------------------------------------------------------------------------------------------
#define IDC_TXT 2052
HWND txt233;
WNDPROC TXT_PROC;
typedef struct tagTXT
{// 
    HWND hWnd;          // handle of owner window
    BOOL x1; //默认是185
    BOOL x2; //默认是170
    LPWSTR in;
} TXT_PARAM;
//
//
LRESULT CALLBACK TXTProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{// 
    PAINTSTRUCT ps;
    HDC hdc;
    HBRUSH br;
    wchar_t txt[40];
    switch (Msg)
    {//
    case WM_PAINT:
    {
        LOGFONT lf;
        HFONT hFont = 0;
        hdc = BeginPaint(hWnd, &ps);
        //br = CreateSolidBrush(RGB(7, 130, 215));
        //FillRect(hdc, &ps.rcPaint, br);
        GetWindowText(hWnd, txt, 40);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, TEXTBLACK);
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"微软雅黑");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, 18, 7, txt, wcslen(txt) /*&ps.rcPaint*//*DT_SINGLELINE | DT_CENTER | DT_VCENTER*/);
        //DeleteObject(br);
        EndPaint(hWnd, &ps);
        break;
    }
    }
    //
    return CallWindowProc(TXT_PROC, hWnd, Msg, wParam, lParam);
}
int Text(
    HWND hWnd,         // handle of owner window
    BOOL x1,
    BOOL x2,
    LPWSTR in
)
{
    static HFONT hFont;
    BTN_PARAM btn;
    btn.hWnd = hWnd;
    hFont = CreateFont(16, 8, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"微软雅黑");//创建字体
    txt233 = CreateWindow(L"static", in, WS_CHILD | WS_VISIBLE | SS_NOTIFY,//默认按钮样式
        x1, x2, 70, 30, hWnd, (HMENU)IDC_TXT, b_hInstance, NULL);
    TXT_PROC = (WNDPROC)SetWindowLong(txt233, GWL_WNDPROC, (LONG)TXTProc);
    return -1;
}
WNDPROC textwnd;
/*UIMAIN头文件 自定义对话框模块--------------------------------------------------------------------------------------------------------------
* 调用方式: TipBox(NULL,"TEXT","TITLE",0)；                                                                                             | *
* 或者:TipBox_D();                                                                                                                     | *
* 关闭按钮已自动包含:CloseBTN                                                                                                            |*
---------------------------------------------------------------------------------------------------------------------------------------*/
#define IDC_CLOSE 496
typedef struct tagMMB
{// 
    HWND hWnd;          // handle 

    LPWSTR lpText;     // text 

    LPWSTR lpCaption;  //  title 

    UINT uType;         // style 

} MMB_PARAM;
//
BOOL CALLBACK DialogProc1(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
    MMB_PARAM* pmmb = (MMB_PARAM*)lParam;
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetWindowText(hwndDlg, pmmb->lpCaption);
        SetWindowText(GetDlgItem(hwndDlg, IDC_STATIC), pmmb->lpText);
        //222222
        Button(hwndDlg,185,170,L"关闭",IDC_CLOSE);
        return TRUE;
    case WM_PAINT:
    {
        HPEN hpen = CreatePen(PS_SOLID,2,RGB(35,35,35));
        HBRUSH br2 = CreateSolidBrush(RGB(35, 35, 35));
        HPEN hpen3 = CreatePen(PS_SOLID, 2, RGB(244, 244, 244));
        HBRUSH br4 = CreateSolidBrush(RGB(244, 244, 244));
        HPEN hpenOld = NULL;
        HDC hdc = NULL;
        HDC hdc2 = NULL;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwndDlg, &ps);
        HBRUSH br = CreateSolidBrush(RGB(60, 60, 60));
        FillRect(hdc, &ps.rcPaint, br);
        SelectObject(hdc, hpen);
        SelectObject(hdc, br2);
        Rectangle(hdc, 0, 0, 455, 30);
        HPEN hpen2 = CreatePen(PS_SOLID, 2, RGB(203, 109, 119));
        HBRUSH br3 = CreateSolidBrush(RGB(203, 109, 119));
        SelectObject(hdc, hpen2);
        SelectObject(hdc, br3);
        RoundRect(hdc,420, 25 ,440, 5, 1, 1);
        //----------------close
        SelectObject(hdc, hpen3);
        SelectObject(hdc, br4);
        MoveToEx(hdc, 422, 22, NULL);
        LineTo(hdc, 437, 7);
        MoveToEx(hdc, 437, 22, NULL);
        LineTo(hdc, 422, 7);
        //----------------
        ReleaseDC(hwndDlg, hdc);//Over                                             // 12
        EndPaint(hwndDlg, &ps);
        DeleteObject(br2);
        DeleteObject(br);
        HRGN hRgn = NULL;
        RECT rect;
        GetClientRect(hwndDlg, &rect);
        hRgn = CreateRoundRectRgn(0, 0, rect.right - rect.left, rect.bottom - rect.top, 6, 6);
        SetWindowRgn(hwndDlg/*窗口句柄*/, hRgn, TRUE);
        return TRUE;
    }
    case WM_CTLCOLORSTATIC:
    {
        if ((HWND)lParam == GetDlgItem(hwndDlg, IDC_STATIC))//2
        {
            SetTextColor((HDC)wParam, RGB(210, 210, 210));
            SetBkMode((HDC)wParam, TRANSPARENT);
        }
        return (INT_PTR)GetStockObject((NULL_BRUSH));//返回一个空画刷(必须)
    }
    case WM_SIZE: //无效但需要存在的代码
    {
        LONG_PTR Style = ::GetWindowLongPtr(hwndDlg, GWL_STYLE);
        Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
        ::SetWindowLongPtr(hwndDlg, GWL_STYLE, Style);
        return TRUE;
    }
    case WM_LBUTTONDOWN:
    {
        if (DlgClose(hwndDlg, lParam) > 0)
        {
            EndDialog(hwndDlg, 0);
            break;
        }
        // 移动窗口 
        SendMessage(hwndDlg, WM_NCLBUTTONDOWN, HTCAPTION, 0);  //向窗口发送WM_NCLBUTTONDOWN消息，HTCAPTION 标题
        break;
    }
    case WM_COMMAND:
    {
        case IDC_CLOSE:
        {
            EndDialog(hwndDlg, 0);
        }
    }
    case WM_CLOSE:
        EndDialog(hwndDlg, 0);
    }
    return FALSE;
}
//
int TipBox(
    HWND hWnd,          // handle 
    LPWSTR lpText,     // text 
    LPWSTR lpCaption,  // title 
    UINT uType          // style 
)
{
    MMB_PARAM mmb;
    mmb.hWnd = hWnd;
    mmb.lpText = lpText;
    mmb.lpCaption = lpCaption;
    mmb.uType = uType;
    DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
        MAKEINTRESOURCE(IDD_TIPBOX), NULL, DialogProc1, (LPARAM)&mmb);
    return -1;
}

#define D_TipBox TipBox
#define B_CLOSE CloseBTN
/*-----------------------------------------------------------------------------------------


-----------------------------------------------------------------------------------------*/
typedef struct tagEDIT
{// 
    HWND hWnd1;          // handle 

    LPWSTR lpText1;     // text 

    LPWSTR lpCaption1;  //  title 

    UINT uType1;         // style 

} EDIT_PARAM;
//
BOOL CALLBACK DialogProc2(HWND hwndDlg1, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
    EDIT_PARAM* emmb = (EDIT_PARAM*)lParam;
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetWindowText(hwndDlg1, emmb->lpCaption1);
        SetWindowText(GetDlgItem(hwndDlg1, IDC_STATIC1), emmb->lpText1);
        Button(hwndDlg1,185,170,L"关闭",IDC_BUTT);
        return TRUE;
    case WM_PAINT:
    {
        HPEN hpen = CreatePen(PS_SOLID, 4, RGB(215, 172, 106));
        HPEN hpenOld = NULL;
        HDC hdc = NULL;
        HDC hdc2 = NULL;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwndDlg1,&ps);
        HBRUSH br = CreateSolidBrush(RGB(60, 60, 60));
        FillRect(hdc, &ps.rcPaint, br);
        SelectObject(hdc, hpen);
        SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
        Rectangle(hdc, 0, 0, 443, 239);
        ReleaseDC(hwndDlg1, hdc);//Over                                             // 12
        EndPaint(hwndDlg1, &ps);
        DeleteObject(br);
        return TRUE;
    }
    case WM_CTLCOLORSTATIC:
    {
        if ((HWND)lParam == GetDlgItem(hwndDlg1, IDC_STATIC1))//2
        {
            SetTextColor((HDC)wParam, RGB(210, 210, 210));
            SetBkMode((HDC)wParam, TRANSPARENT);
        }
        return (INT_PTR)GetStockObject((NULL_BRUSH));//返回一个空画刷(必须)
    }
    case WM_LBUTTONDOWN:
    {
        if (DlgClose(hwndDlg1, lParam) > 0)
        {
            DeleteObject(hBitmap);
            DeleteObject(hFont);
            EndDialog(hwndDlg1, 0);
            break;
        }
        // 移动窗口 
        SendMessage(hwndDlg1, WM_NCLBUTTONDOWN, HTCAPTION, 0);  //向窗口发送WM_NCLBUTTONDOWN消息，HTCAPTION 标题
        break;
    }
    case WM_COMMAND:
    {
    case IDC_BUTT:
    {
        EndDialog(hwndDlg1, 0);
    }
    }
    case WM_CLOSE:
        EndDialog(hwndDlg1, 0);
    }
    return FALSE;
}
//
int ActBox(
    HWND hWnd1,          // handle 
    LPWSTR lpText,     // text 
    LPWSTR lpCaption,  // title 
    UINT uType          // style 
)
{
    EDIT_PARAM edit1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
    edit1.hWnd1 = hWnd1;
    edit1.lpText1 = lpText;
    edit1.lpCaption1 = lpCaption;
    edit1.uType1 = uType;
    DialogBoxParam((HINSTANCE)GetWindowLong(hWnd1, GWL_HINSTANCE),
        MAKEINTRESOURCE(IDD_DIALOG3), NULL, DialogProc2, (LPARAM)&edit1);
    return -1;
}

#define ACTBOX ActBox
/*-----------------------------------------------------------------------------------------
如果要提示一个错误消息，并且以高视觉对比进行警告，用FatalBox.
-----------------------------------------------------------------------------------------*/
typedef struct tagMMB1
{// 
    HWND hWnd;          // handle 

    LPWSTR lpText;     // text 

    LPWSTR lpCaption;  //  title 

    UINT uType;         // style 

} MMB_PARAM1;
//
BOOL CALLBACK DialogProc3(HWND hwndDlg2, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
    MMB_PARAM1* pmmb = (MMB_PARAM1*)lParam;
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetWindowText(hwndDlg2, pmmb->lpCaption);
        SetWindowText(GetDlgItem(hwndDlg2, IDC_STATIC1), pmmb->lpText);
        //222222
        Button(hwndDlg2,185,170,L"关闭",IDC_BUTT);
        return TRUE;
    case WM_PAINT:
    {
        HPEN hpen = CreatePen(PS_SOLID, 4, RGB(50, 50, 50));
        HPEN hpenOld = NULL;
        HDC hdc = NULL;
        HDC hdc2 = NULL;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwndDlg2, &ps);
        HBRUSH br = CreateSolidBrush(RGB(228, 20, 0));
        FillRect(hdc, &ps.rcPaint, br);
        SelectObject(hdc, hpen);
        SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
        Rectangle(hdc, 0, 0, 443, 239);
        ReleaseDC(hwndDlg2, hdc);//Over                                             // 12
        EndPaint(hwndDlg2, &ps);
        DeleteObject(br);
        return TRUE;
    }
    case WM_CTLCOLORSTATIC:
    {
            if ((HWND)lParam == GetDlgItem(hwndDlg2, IDC_STATIC1))//2
            {
                SetTextColor((HDC)wParam, RGB(210, 210, 210));
                SetBkMode((HDC)wParam, TRANSPARENT);
            }
            return (INT_PTR)GetStockObject((NULL_BRUSH));//返回一个空画刷(必须)
    }
    case WM_SIZE: //无效但需要存在的代码
    {
        LONG_PTR Style = ::GetWindowLongPtr(hwndDlg2, GWL_STYLE);
        Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
        ::SetWindowLongPtr(hwndDlg2, GWL_STYLE, Style);
        return TRUE;
    }
    case WM_LBUTTONDOWN:
    {
        //if (DlgClose(hwndDlg2, lParam) > 0)
       // {
            //DeleteObject(hBitmap);
            //DeleteObject(hFont);
           // EndDialog(hwndDlg2, 0);
            //break;
        //}
        // 移动窗口 
        //SendMessage(hwndDlg2, WM_NCLBUTTONDOWN, HTCAPTION, 0);  //向窗口发送WM_NCLBUTTONDOWN消息，HTCAPTION 标题
        break;
    }
    case WM_COMMAND:
    {
    case IDC_BUTT:
    {
        EndDialog(hwndDlg2, 0);
    }
    }
    case WM_CLOSE:
        EndDialog(hwndDlg2, 0);
    }
    return FALSE;
}
//
int FatalBox(
    HWND hWnd,          // handle 
    LPWSTR lpText,     // text 
    LPWSTR lpCaption,  // title 
    UINT uType          // style 
)
{
    MMB_PARAM1 mmb;
    mmb.hWnd = hWnd;
    mmb.lpText = lpText;
    mmb.lpCaption = lpCaption;
    mmb.uType = uType;
    DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
        MAKEINTRESOURCE(IDD_DIALOG3), NULL, DialogProc3, (LPARAM)&mmb);
    return -1;
}
//----------------------------------------------------
typedef struct tagMMB3
{// 
    HWND hWnd1;          // handle 

    LPWSTR lpText1;     // text 

    LPWSTR lpCaption1;  //  title 

    UINT uType1;         // style 

} MMB_PARAM2;
//
BOOL CALLBACK DialogProcN(HWND hwndDlgi, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
    MMB_PARAM* pmmb = (MMB_PARAM*)lParam;
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetWindowText(hwndDlgi, pmmb->lpCaption);
        SetWindowText(GetDlgItem(hwndDlgi, IDC_STATIC), pmmb->lpText);
        //222222
        Button(hwndDlgi,185,170,L"关闭",IDC_BUTT);
        return TRUE;
    case WM_PAINT:
    {
        HPEN hpen = CreatePen(PS_SOLID, 2, RGB(35, 35, 35));
        HBRUSH br2 = CreateSolidBrush(RGB(35, 35, 35));
        HPEN hpen3 = CreatePen(PS_SOLID, 2, RGB(244, 244, 244));
        HBRUSH br4 = CreateSolidBrush(RGB(244, 244, 244));
        HPEN hpenOld = NULL;
        HDC hdc = NULL;
        HDC hdc2 = NULL;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwndDlgi, &ps);
        HBRUSH br = CreateSolidBrush(RGB(60, 60, 60));
        FillRect(hdc, &ps.rcPaint, br);
           TRIVERTEX vert[2];

            GRADIENT_RECT gRect;



            vert[0].x = 0;

            vert[0].y = 0;

            vert[0].Red = 0x0000;

            vert[0].Green = 0xc000;

            vert[0].Blue = 0xff00;

            vert[0].Alpha = 0x0000;



            vert[1].x = 453;

            vert[1].y = 30;

            vert[1].Red = 0x0000;

            vert[1].Green = 0xcf00;

            vert[1].Blue = 0x4ff0;

            vert[1].Alpha = 0x0000;



            gRect.UpperLeft = 0;

            gRect.LowerRight = 1;



            GradientFill(hdc, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
        //--------------------
        HPEN hpen2 = CreatePen(PS_SOLID, 2, RGB(203, 109, 119));
        HBRUSH br3 = CreateSolidBrush(RGB(203, 109, 119));
        SelectObject(hdc, hpen2);
        SelectObject(hdc, br3);
        RoundRect(hdc, 420, 25, 440, 5, 1, 1);
        //----------------close
        SelectObject(hdc, hpen3);
        SelectObject(hdc, br4);
        MoveToEx(hdc, 422, 22, NULL);
        LineTo(hdc, 437, 7);
        MoveToEx(hdc, 437, 22, NULL);
        LineTo(hdc, 422, 7);
        //----------------
        ReleaseDC(hwndDlgi, hdc);//Over                                             // 12
        EndPaint(hwndDlgi, &ps);
        DeleteObject(br2);
        DeleteObject(br);  
        HRGN hRgn = NULL;
        RECT rect;
        GetClientRect(hwndDlgi, &rect);
        hRgn = CreateRoundRectRgn(0, 0, rect.right - rect.left, rect.bottom - rect.top, 6, 6);
        SetWindowRgn(hwndDlgi/*窗口句柄*/, hRgn, TRUE);
        return TRUE;
    }
    case WM_CTLCOLORSTATIC:
    {
        if ((HWND)lParam == GetDlgItem(hwndDlgi, IDC_STATIC))//2
        {
            SetTextColor((HDC)wParam, RGB(210, 210, 210));
            SetBkMode((HDC)wParam, TRANSPARENT);
        }
        return (INT_PTR)GetStockObject((NULL_BRUSH));//返回一个空画刷(必须)
    }
    case WM_SIZE: //无效但需要存在的代码
    {
        LONG_PTR Style = ::GetWindowLongPtr(hwndDlgi, GWL_STYLE);
        Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
        ::SetWindowLongPtr(hwndDlgi, GWL_STYLE, Style);
        return TRUE;
    }
    case WM_LBUTTONDOWN:
    {
        if (DlgClose(hwndDlgi, lParam) > 0)
        {
            EndDialog(hwndDlgi, 0);
            break;
        }
        // 移动窗口 
        SendMessage(hwndDlgi, WM_NCLBUTTONDOWN, HTCAPTION, 0);  //向窗口发送WM_NCLBUTTONDOWN消息，HTCAPTION 标题
        break;
    }
    case WM_COMMAND:
    {
    case IDC_BUTT:
    {
        EndDialog(hwndDlgi, 0);
    }
    }
    case WM_CLOSE:
        EndDialog(hwndDlgi, 0);
    }
    return FALSE;
}
//
int GBox(
    HWND hWnd1,          // handle 
    LPWSTR lpText1,     // text 
    LPWSTR lpCaption1,  // title 
    UINT uType1          // style 
)
{
    MMB_PARAM2 mmb;
    mmb.hWnd1 = hWnd1;
    mmb.lpText1 = lpText1;
    mmb.lpCaption1 = lpCaption1;
    mmb.uType1 = uType1;
    DialogBoxParam((HINSTANCE)GetWindowLong(hWnd1, GWL_HINSTANCE),
        MAKEINTRESOURCE(IDD_TIPBOX), NULL, DialogProcN, (LPARAM)&mmb);
    return -1;
}

#define G_TipBox GBox
//------------------------------------------------------------------------------------------
#include "Update.h"
typedef struct tagEDIT1
{// 

    HWND hWnd11;          // handle 

    LPWSTR lpText11;     // text 

    LPWSTR lpCaption11;  //  title 

    UINT uType11;         // style 

} EDIT_PARAM1;
//
BOOL CALLBACK DialogProc12(HWND hwndDlg11, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
    EDIT_PARAM1* emmb = (EDIT_PARAM1*)lParam;
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetWindowText(hwndDlg11, emmb->lpCaption11);
        SetWindowText(GetDlgItem(hwndDlg11, IDC_STATIC99), emmb->lpText11);
        Button(hwndDlg11,185,170, L"关闭",IDC_BUTT);
        return TRUE;
    case WM_PAINT:
    {
        HPEN hpen = CreatePen(PS_SOLID, 2, RGB(215, 122, 106));
        HPEN hpenOld = NULL;
        HDC hdc = NULL;
        HDC hdc2 = NULL;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwndDlg11, &ps);
        HBRUSH br = CreateSolidBrush(RGB(60, 60, 60));
        FillRect(hdc, &ps.rcPaint, br);
        SelectObject(hdc, hpen);
        SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
        Rectangle(hdc, 0, 0, 174, 193);
        ReleaseDC(hwndDlg11, hdc);//Over                                             // 12
        EndPaint(hwndDlg11, &ps);
        DeleteObject(br);
        return TRUE;
    }
    case WM_CTLCOLORSTATIC:
    {
        if ((HWND)lParam == GetDlgItem(hwndDlg11, IDC_STATIC99)) //2
        {
            SetTextColor((HDC)wParam, RGB(210, 210, 210));
            SetBkMode((HDC)wParam, TRANSPARENT);
        }
        return (INT_PTR)GetStockObject((NULL_BRUSH));//返回一个空画刷(必须)
    }
    case WM_LBUTTONDOWN:
    {
        if (DlgClose(hwndDlg11, lParam) > 0)
        {
            DeleteObject(hBitmap);
            DeleteObject(hFont);
            EndDialog(hwndDlg11, 0);
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
            EndDialog(hwndDlg11, 0);
            break;
        }
    }
    case WM_COMMAND:
    {
    case IDC_BUTT:
    {
        EndDialog(hwndDlg11, 0);
    }
    }
    case WM_CLOSE:
        EndDialog(hwndDlg11, 0);
    }
    return FALSE;
}
//
int PopBox(
    HWND hWnd11,          // handle 
    LPWSTR lpText11,     // text 
    LPWSTR lpCaption11,  // title 
    UINT uType11          // style 
)
{
    EDIT_PARAM edit11;
    edit11.hWnd1 = hWnd11;
    edit11.lpText1 = lpText11;
    edit11.lpCaption1 = lpCaption11;
    edit11.uType1 = uType11;
    DialogBoxParam((HINSTANCE)GetWindowLong(hWnd11, GWL_HINSTANCE),
        MAKEINTRESOURCE(IDD_DIALOG4), NULL, DialogProc12, (LPARAM)&edit11);
    return -1;
}

#define POPBOX PopBox

//-----------------------------------------------------------------------------------------
typedef struct tagNNN
{// 
    HWND hWnd;          // handle 

    LPWSTR lpText;     // text 

    LPWSTR lpCaption;  //  title 

    UINT uType;         // style 

} NNN_PARAM;
//
BOOL CALLBACK NEWProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
    MMB_PARAM* pmmb = (MMB_PARAM*)lParam;
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetWindowText(hwndDlg, pmmb->lpCaption);
        SetWindowText(GetDlgItem(hwndDlg, IDC_STATIC), pmmb->lpText);
        //222222
        Button(hwndDlg, 355, 165, L"关闭", IDC_CLOSE);
        return TRUE;
    case WM_NCPAINT:
    {
        HDC hdc;
        hdc = GetDCEx(hwndDlg, (HRGN)wParam, DCX_WINDOW | DCX_INTERSECTRGN);
        PAINTSTRUCT ps;
        RECT rect;
        HBRUSH hbr = CreateSolidBrush(RGB(0, 255, 255));
        hbr = (HBRUSH)SelectObject(hdc, hbr);
        //填充标题栏颜色
        Rectangle(hdc, 0, 0, 40, 200);
        ReleaseDC(hwndDlg, hdc);
        /*
        HRGN hRgn = NULL;
        RECT rect;
        GetClientRect(hwndDlg, &rect);
        hRgn = CreateRoundRectRgn(0, 0, rect.right - rect.left, rect.bottom - rect.top, 6, 6);
        SetWindowRgn(hwndDlg/*窗口句柄*//*, hRgn, TRUE);
        */
    }
    case WM_PAINT:
    {
        HPEN hpen = CreatePen(PS_SOLID, 2, RGB(35, 35, 35));
        HBRUSH br2 = CreateSolidBrush(RGB(35, 35, 35));
        HPEN hpen3 = CreatePen(PS_SOLID, 2, RGB(244, 244, 244));
        HBRUSH br4 = CreateSolidBrush(RGB(244, 244, 244));
        HPEN hpenOld = NULL;
        HDC hdc = NULL;
        HDC hdc2 = NULL;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwndDlg, &ps);
        HBRUSH br = CreateSolidBrush(RGB(60, 60, 60));
        FillRect(hdc, &ps.rcPaint, br);
        //----------------
        ReleaseDC(hwndDlg, hdc);//Over                                             // 12
        EndPaint(hwndDlg, &ps);
        DeleteObject(br);
        return TRUE;
    }
    case WM_CTLCOLORSTATIC:
    {
        if ((HWND)lParam == GetDlgItem(hwndDlg, IDC_STATIC))//2
        {
            SetTextColor((HDC)wParam, RGB(210, 210, 210));
            SetBkMode((HDC)wParam, TRANSPARENT);
        }
        return (INT_PTR)GetStockObject((NULL_BRUSH));//返回一个空画刷(必须)
    }
    /*
    case WM_SIZE: //无效但需要存在的代码
    {
        LONG_PTR Style = ::GetWindowLongPtr(hwndDlg, GWL_STYLE);
        Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
        ::SetWindowLongPtr(hwndDlg, GWL_STYLE, Style);
        return TRUE;
    }
    */
    case WM_LBUTTONDOWN:
    {
        if (DlgClose(hwndDlg, lParam) > 0)
        {
            EndDialog(hwndDlg, 0);
            break;
        }
        // 移动窗口 
        SendMessage(hwndDlg, WM_NCLBUTTONDOWN, HTCAPTION, 0);  //向窗口发送WM_NCLBUTTONDOWN消息，HTCAPTION 标题
        break;
    }
    case WM_COMMAND:
    {
    case IDC_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    }
    case WM_CLOSE:
        EndDialog(hwndDlg, 0);
    }
    return FALSE;
}
//
int MsgBox(
    HWND hWnd,          // handle 
    LPWSTR lpText,     // text 
    LPWSTR lpCaption,  // title 
    UINT uType          // style 
)
{
    NNN_PARAM mmb;
    mmb.hWnd = hWnd;
    mmb.lpText = lpText;
    mmb.lpCaption = lpCaption;
    mmb.uType = uType;
    DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
        MAKEINTRESOURCE(IDD_TIPBOX1), NULL, NEWProc, (LPARAM)&mmb);
    return -1;
}
/*-----------------------------------------------------------------------------------------
struct OVER
-----------------------------------------------------------------------------------------*/

