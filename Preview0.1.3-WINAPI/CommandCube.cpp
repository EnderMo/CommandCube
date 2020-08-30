// FrameworkUI.cpp : 定义应用程序的入口点。
//
#include "UIMain.h"
#include "framework.h"
#include "CommandCube.h"
#include "function.h"
#include "UILibEx.h"
#include "UIdef.hpp"
#include "CommandCubeFramework.hpp"
#include "Windesktop.h"
//C++ Normal_____________________________________________________;
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "rpcrt4.lib") 
#pragma comment(lib, "COMCTL32.LIB")
#include <Wininet.h>

#pragma comment(lib,"Urlmon.lib")

#pragma comment(lib, "Wininet.lib")
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windowsx.h>
#include "Update.h"
#include "dwmapi.h"
#include <gdiplus.h>
//----
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib,"dwmapi.lib")
#define IDC_2 1002
#define IDC_3 2002

#pragma warning(disable:4996);

HINSTANCE g_hInstance;
HWND c_hwnd;
HWND gwnd;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK BtnProc2(HWND, UINT, WPARAM, LPARAM);//按钮2
//------------------------------------------------------------------------------------------------------------------------
//在这里编写全局函数
// for easy replace ，set UUUUIIDD=WWWWWWWW-XXXX-YYYY-ZZZZ-WWWWWWWWWWWW ！
// 这个函数只要运行 一次 ！
//全局函数声明结束。
//-------------------------------------------------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // TODO: 在此处放置您的代码.
    g_hInstance = hInstance;
    TCHAR className[] = TEXT("my class");
    TCHAR szBtnName2[] = TEXT("MyBtn2");
    TCHAR szBtnName3[] = TEXT("MyBtn3");
    WNDCLASS wndclass = { 0 };
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (CreateSolidBrush(RGB(255,255,255)));
    wndclass.lpszClassName = className;
    wndclass.lpfnWndProc = WindowProc;
    wndclass.hIcon = LoadIcon(g_hInstance,MAKEINTRESOURCE(IDI_SMALL));
    wndclass.hCursor = LoadCursor(NULL, (IDC_ARROW));
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
     
    RegisterClass(&wndclass);
     
    HWND hMain = CreateWindow(className, L"CommandCube", WS_OVERLAPPEDWINDOW, 300, 300, 832, 512, NULL, NULL, hInstance, NULL);
     

    if (!hMain)
    {
        TipBox(NULL,L"类注册出现错误.\n\n这是一个内部错误,请尝试重新启动程序.\n\n本错误未被定义,如果代码出现问题,本错误也可能出现.",L"SOMETHING WRONG!",0);
        return 0;
    }

    ShowWindow(hMain, SW_SHOW);
     
    MSG msg;
    BOOL ret;
    while (ret = GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
     
    return 0;
}
//自定样式声明模块
#define test 10492
#include "CommandExc.h"
#include "zip.h"
#include "unzip.h"
//主窗口过程                                                                                                                                  PROC
#define DDISPLAY 1033
#define TITLEBTN 0x11c3
#define CLOSE 0x11c4
#define IDC_MINIMIZE 0x11c5
#define IDC_MENUBOX 0x11c6
#define CmdTab 0x11c7
#define ExtTab 0x11c8
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HFONT hFont;//定义静态字体变量
    static HWND close;
    static HWND MINIMIZE;
    static HWND txt1;
    static HWND txt2;
    static HWND bt1;
    static int msLast=WM_MOUSELEAVE;
    char txt[40];
    HDC         hdc =NULL;
    HDC hdc2 = NULL;
    HDC         hdcMem;
    HBRUSH br = NULL;
    HPEN hpen;
    HPEN hpenOld;
    BOOL fActive;

    PAINTSTRUCT ps;
    HINSTANCE      hInstance = NULL;
    BITMAP         bitmap;


    static int      bmWidth, bmHeight;       // 2 静态变量

    //WCHAR Ver[80];
    //Verstr; wcscat(Ver, L"\r\nXXXX");
    Verstr; wcscat(Ver, L"\n\nBy 末影小末EnderMo  |  bilibili:373454723  |  官方:endermo.xyz");

    //格式化
    RECT rect;
    GetClientRect(hwnd, &rect);
    switch (uMsg)
    {
    case WM_CREATE:
        {
        //STRUCT TITLEBAR
        LargeTitlebtn(hwnd, 1, 1, 160, 50, L"CommandCube", TITLEBTN);
        FrameClose(hwnd, rect.right - 20, 16, CLOSE);
        FrameMinimize(hwnd, rect.right - 60, 16,IDC_MINIMIZE);
        FrameMenuBox(hwnd, rect.right - 100, 16, IDC_MENUBOX);
        //STRUCT SIDEBAR
        CCTAB(hwnd, 1, 120, 160, 40, L"命令块", CmdTab);
        CCTAB(hwnd, 1, 160, 160, 40, L"扩展", ExtTab);
        //STRUCT CONTROL
        ConsoleUI(hwnd, rect.left + 161, 51, 669, 459, SW_SHOW);
        }
    case WM_PAINT:
    {
        HRGN hRgn = NULL;

        HBRUSH hbr = NULL;
        //HPEN hpen = NULL

        hdc = BeginPaint(hwnd, &ps);

        /*
        hRgn = CreateRoundRectRgn(0, 0, rect.right - rect.left, rect.bottom - rect.top, 6, 6);
        SetWindowRgn(hwnd/*窗口句柄*//* hRgn, TRUE);*/
      

        HPEN hpen = NULL;

        DrawTitleBar(hdc, rect.right - rect.left, 51, LBLUE);

        DrawSideBar(hdc, 161, rect.bottom, SideGrey);

        DrawFrame(hdc, hpen,rect, 2, RGB(1, 1, 1));

        ReleaseDC(hwnd, hdc);//Over      
        DeleteObject(hpen);
        EndPaint(hwnd, &ps);                                             // 13
        UpdateWindow(hwnd);
        break;
    }
    case WM_SIZE:
    {
        LONG_PTR Style = ::GetWindowLongPtr(hwnd, GWL_STYLE);
        Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
        ::SetWindowLongPtr(hwnd, GWL_STYLE, Style);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        // 移动窗口 
        SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);  //向窗口发送WM_NCLBUTTONDOWN消息，HTCAPTION 标题
        break;
    }
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDC_2:
                {
                    break;
                }
                case TITLEBTN:
                {
                    TipBox(hwnd, Ver, L"CommandCube", NULL);
                    break;
                }
                case CLOSE:
                {
                    AnimateWindow(hwnd, 400, AW_HIDE | AW_BLEND  );
                    PostQuitMessage(0);
                    break;
                }
                case IDC_MINIMIZE:
                {
                    SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0); // 最小化
                    break;
                }
                case IDC_MENUBOX:
                {
                    MenuBox(hwnd, L"检查更新                ", L"更多", NULL);
                    break;
                }
                case CmdTab:
                {
                    ConsoleUI(hwnd, rect.left + 161, 51, 669, 459, SW_SHOW);
                    break;
                }
                case ExtTab:
                {
                    EXTUI(hwnd);
                    break;
                }
                break;
            }
            break;
        }
    case WM_CLOSE:
    {
        SendMessage(hwnd, WM_PAINT | WM_PRINT | WM_PRINTCLIENT, wParam, NULL);
        AnimateWindow(hwnd, 400, AW_HIDE | AW_BLEND);
        PostQuitMessage(0);
        break;
    }
    case WM_ACTIVATE:

        fActive = LOWORD(wParam);
        hdc = GetDC(hwnd);
        if (fActive == WA_ACTIVE)
        {
            HRGN hRgn = NULL;
            HBRUSH hbr = NULL;
            HPEN hpen = NULL;
            hpen = CreatePen(PS_SOLID, 2, RGB(96, 60, 186));
            SelectObject(hdc, hpen);
            SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
            Rectangle(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top);
            ReleaseDC(hwnd, hdc);//Over      
        }
        else
        {
            HRGN hRgn = NULL;
            HBRUSH hbr = NULL;
            HPEN hpen = NULL;
            //hpen = CreatePen(PS_SOLID, 4, RGB(0, 122, 204));
            hpen = CreatePen(PS_SOLID, 2, RGB(1,1,1));
            SelectObject(hdc, hpen);
            SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
            Rectangle(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top);
            ReleaseDC(hwnd, hdc);//Over   
        }
        
        break;

    }
     
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
//________________________________________________________________________________________________UUID POP___________________________________