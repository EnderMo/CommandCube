#pragma once
#include "framework.h"
#include "Colordef.h"
HWND t_bt1;
HWND t_bt2;
HWND b_cloase;
HWND b_minimize;
WNDPROC TToldProc;
HINSTANCE f_hinst;
typedef struct tagTITLEBTN
{// 
    HWND hWnd;          // handle of owner window
    BOOL x1; //默认是185
    BOOL x2; //默认是170
    BOOL rcx1;
    BOOL rcy1;
    LPWSTR in;
    UINT style;
} TT_PX;
//
//
LRESULT CALLBACK TITLEProcX(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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
        br = CreateSolidBrush(DEEPBLUE);
        //br = CreateSolidBrush(RGB(7, 130, 215));
        FillRect(hdc, &rc, br);
        GetWindowText(hWnd, txt, 40);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(255, 255, 255));
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, 16, 14, txt, wcslen(txt) /*&ps.rcPaint*//*DT_SINGLELINE | DT_CENTER | DT_VCENTER*/);
        //DrawText(hdc, txt, wcslen(txt), &ps.rcPaint, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        ReleaseDC(hWnd, hdc);
        UpdateWindow(hWnd);
        DeleteObject(br);
        EndPaint(hWnd, &ps);
        break;
    }
    }
    //
    return CallWindowProc(TToldProc, hWnd, Msg, wParam, lParam);
}
//________________HWND 主窗口,__x1 x坐标,__x2 y坐标,[面积]L"按钮文字",从定义获取控件
//如果需要进行消息处理,case IDC_XX:
int LargeTitlebtn(
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
    TT_PX btn;
    btn.hWnd = hWnd;
    btn.style = style;
    t_bt1 = CreateWindow(L"Button", in, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,//默认按钮样式
        x1, x2, rcx1, rcy1, hWnd, (HMENU)style, f_hinst, NULL);
    TToldProc = (WNDPROC)SetWindowLong(t_bt1, GWL_WNDPROC, (LONG)TITLEProcX);
    return -1;
}
//-------------------------------------------------------
HWND CCtab;
WNDPROC TabProc;
LRESULT CALLBACK CCTab(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{// 
    PAINTSTRUCT ps;
    HDC hdc = NULL;
    RECT rc;
    GetClientRect(hWnd, &rc);
    LOGFONT lf;
    HFONT hFont = 0;
    HBRUSH br;
    TCHAR txt[40];
    BOOL fActive;
    switch (Msg)
    {//
      
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        br = CreateSolidBrush(SideGrey_s);
        //br = CreateSolidBrush(RGB(7, 130, 215));
        FillRect(hdc, &rc, br);
        GetWindowText(hWnd, txt, 40);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(255, 255, 255));
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, 16, 11, txt, wcslen(txt) );
        //DrawText(hdc, txt, wcslen(txt), &ps.rcPaint, DT_SINGLELINE | DT_;
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
        hbr = CreateSolidBrush(SideGrey_s);
        FillRect(hdc, &rc, hbr);
        GetWindowText(hWnd, txt, 40);
        SetTextColor(hdc, T_LIGHT);
        SetBkMode(hdc, TRANSPARENT);
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, 16, 11, txt, wcslen(txt) );
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
        hbr = CreateSolidBrush(LBLUE);
        FillRect(hdc, &rc, hbr);
        GetWindowText(hWnd, txt, 40);
        SetTextColor(hdc, T_LIGHT);
        SetBkMode(hdc, TRANSPARENT);
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, 16, 11, txt, wcslen(txt));
        //SetWindowText(hWnd, L"关闭");
        ReleaseDC(hWnd, hdc);
        //SetWindowText(hWnd, L"[关闭]");
        DeleteObject(hbr);
        OutputDebugStringA("Over\n");
        break;
    }
    
    }
    //
    return CallWindowProc(TabProc, hWnd, Msg, wParam, lParam);
}
//________________HWND 主窗口,__x1 x坐标,__x2 y坐标,[面积]L"按钮文字",从定义获取控件
//如果需要进行消息处理,case IDC_XX:
int CCTAB(
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
    TT_PX btn;
    btn.hWnd = hWnd;
    btn.style = style;
    CCtab = CreateWindow(L"button", in, WS_VISIBLE | WS_CHILD | BS_TEXT | BS_PUSHBUTTON | BS_OWNERDRAW | WS_OVERLAPPED  ,//默认按钮样式
        x1, x2, rcx1, rcy1, hWnd, (HMENU)style, f_hinst, NULL);
    TabProc = (WNDPROC)SetWindowLong(CCtab, GWL_WNDPROC, (LONG)CCTab);
    return -1;
}
//-------------------------------------------------------
HINSTANCE FHINST;
HWND fcls;
typedef struct tagCLOSE
{// 
    HWND hWnd;          // handle of owner window
    BOOL x1; //默认是185
    BOOL x2; //默认是170
    LPWSTR in;
    UINT style;
} CLOASE_PARAM;
//
//
LRESULT CALLBACK BTclose(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{// 
    PAINTSTRUCT ps;
    HDC hdc = NULL;
    RECT rc;
    GetClientRect(hWnd, &rc);
    LOGFONT lf;
    HFONT hFont = 0;
    HBRUSH br;
    HPEN hpen;
    TCHAR txt[40];
    switch (Msg)
    {//
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        hpen = CreatePen(PS_SOLID, 2, RGB(244, 244, 244));
        SelectObject(hdc, hpen);
        MoveToEx(hdc, 0, 0, NULL);
        LineTo(hdc, 16, 16);
        MoveToEx(hdc, 16, 0, NULL);
        LineTo(hdc, 0, 16);
        ReleaseDC(hWnd, hdc);
        UpdateWindow(hWnd);
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
        hbr = CreateSolidBrush(peachred);
        hpen = CreatePen(PS_SOLID, 2, RGB(244, 244, 244));
        SelectObject(hdc, hbr);
        FillRect(hdc, &rc, hbr);
        SelectObject(hdc, hpen);
        MoveToEx(hdc, 0, 0, NULL);
        LineTo(hdc, 16, 16);
        MoveToEx(hdc, 16, 0, NULL);
        LineTo(hdc, 0, 16);
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
int FrameClose(
    HWND hWnd,         // handle of owner window
    BOOL x1,
    BOOL x2,

    UINT style //从定义获取按钮控件依赖
)
{
    static HFONT hFont;
    CLOASE_PARAM btn;
    btn.hWnd = hWnd;
    btn.style = style;
    fcls = CreateWindow(L"Button", NULL, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,//默认按钮样式
        x1, x2, 18, 18, hWnd, (HMENU)style, FHINST, NULL);
    BToldProc = (WNDPROC)SetWindowLong(fcls, GWL_WNDPROC, (LONG)BTclose);
    return -1;
}
//----------------------------------------
HWND fmmz;
typedef struct tagMMZ
{// 
    HWND hWnd;          // handle of owner window
    BOOL x1; //默认是185
    BOOL x2; //默认是170
    LPWSTR in;
    UINT style;
} MMZ_PARAM;
//
//
LRESULT CALLBACK FrameMinimizeProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{// 
    PAINTSTRUCT ps;
    HDC hdc = NULL;
    RECT rc;
    GetClientRect(hWnd, &rc);
    LOGFONT lf;
    HFONT hFont = 0;
    HBRUSH br;
    HPEN hpen;
    TCHAR txt[40];
    switch (Msg)
    {//
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        hpen = CreatePen(PS_SOLID, 2, RGB(244, 244, 244));
        SelectObject(hdc, hpen);
        MoveToEx(hdc, 0, 8, NULL);
        LineTo(hdc, 16, 8);
        ReleaseDC(hWnd, hdc);
        UpdateWindow(hWnd);
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
        hbr = CreateSolidBrush(SBLUE);
        hpen = CreatePen(PS_SOLID, 2, RGB(244, 244, 244));
        SelectObject(hdc, hbr);
        FillRect(hdc, &rc, hbr);
        SelectObject(hdc, hpen);
        MoveToEx(hdc, 16, 8, NULL);
        LineTo(hdc, 0, 8);
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
int FrameMinimize(
    HWND hWnd,         // handle of owner window
    BOOL x1,
    BOOL x2,

    UINT style //从定义获取按钮控件依赖
)
{
    static HFONT hFont;
    MMZ_PARAM btn;
    btn.hWnd = hWnd;
    btn.style = style;
    fmmz = CreateWindow(L"Button", NULL, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,//默认按钮样式
        x1, x2, 18, 18, hWnd, (HMENU)style, FHINST, NULL);
    BToldProc = (WNDPROC)SetWindowLong(fmmz, GWL_WNDPROC, (LONG)FrameMinimizeProc);
    return -1;
}
//----------------------------------------
HWND fmenu;
typedef struct tagMBX
{// 
    HWND hWnd;          // handle of owner window
    BOOL x1; //默认是185
    BOOL x2; //默认是170
    LPWSTR in;
    UINT style;
} MBX_PARAM;
//
//
LRESULT CALLBACK FrameMenuProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{// 
    PAINTSTRUCT ps;
    HDC hdc = NULL;
    RECT rc;
    GetClientRect(hWnd, &rc);
    LOGFONT lf;
    HFONT hFont = 0;
    HBRUSH br;
    HPEN hpen;
    TCHAR txt[40];
    switch (Msg)
    {//
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        hpen = CreatePen(PS_SOLID, 2, RGB(244, 244, 244));
        br = CreateSolidBrush(RGB(244, 244, 244));
        SelectObject(hdc, hpen);
        SelectObject(hdc, br);
        Rectangle(hdc, -1, 2, 3, 3);
        Rectangle(hdc, 5, 2, 18, 3);
        Rectangle(hdc, -1, 8, 3, 9);
        Rectangle(hdc, 5, 8, 18, 9);
        Rectangle(hdc, -1, 14, 3, 15);
        Rectangle(hdc, 5, 14, 18, 15);
        ReleaseDC(hWnd, hdc);
        UpdateWindow(hWnd);
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
        hbr = CreateSolidBrush(SBLUE);
        hpen = CreatePen(PS_SOLID, 2, RGB(244, 244, 244));
        br = CreateSolidBrush(RGB(244, 244, 244));
        SelectObject(hdc, hbr);
        FillRect(hdc, &rc, hbr);
        SelectObject(hdc, hpen);
        SelectObject(hdc, br);
        Rectangle(hdc, -1, 2, 3, 3);
        Rectangle(hdc, 5, 2, 18, 3);
        Rectangle(hdc, -1, 8, 3, 9);
        Rectangle(hdc, 5, 8, 18, 9);
        Rectangle(hdc, -1, 14, 3, 15);
        Rectangle(hdc, 5, 14, 18, 15);
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
int FrameMenuBox(
    HWND hWnd,         // handle of owner window
    BOOL x1,
    BOOL x2,

    UINT style //从定义获取按钮控件依赖
)
{
    static HFONT hFont;
    MBX_PARAM btn;
    btn.hWnd = hWnd;
    btn.style = style;
    fmenu = CreateWindow(L"Button", NULL, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,//默认按钮样式
        x1, x2, 18, 18, hWnd, (HMENU)style, FHINST, NULL);
    BToldProc = (WNDPROC)SetWindowLong(fmenu, GWL_WNDPROC, (LONG)FrameMenuProc);
    return -1;
}

//-------------------------------------------
void DrawTitleBar(HDC hdc, BOOL x1, BOOL y1, COLORREF cl)
{
    HPEN hpen = CreatePen(PS_SOLID, 0, cl);
    HBRUSH hbr = CreateSolidBrush(cl);
    SelectObject(hdc, hpen);
    SelectObject(hdc, hbr);
    Rectangle(hdc, 0, 0, x1, y1);
}
void DrawFrame(HDC hdc, HPEN hpen,RECT rect, BOOL wid, COLORREF cl)
{
    hpen = CreatePen(PS_SOLID, wid, cl);
    SelectObject(hdc, hpen);
    SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
    Rectangle(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top);
}
void DrawSideBar(HDC hdc, BOOL x1, BOOL y1, COLORREF cl)
{
    HPEN hpen = CreatePen(PS_SOLID, 0, cl);
    HBRUSH hbr = CreateSolidBrush(cl);
    SelectObject(hdc, hpen);
    SelectObject(hdc, hbr);
    Rectangle(hdc, 0, 50, x1, y1);
}