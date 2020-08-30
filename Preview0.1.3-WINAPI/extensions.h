#pragma once
#include "framework.h"
#include "Windesktop.h"
#include "Colordef.h"
#include "UILibEx.h"
#include "UIMain.h"
#include "zip.h"
#include "unzip.h"
#include "core.h"
//#include "filedlg.h"

static TCHAR     szFileName[MAX_PATH], szTitleName[MAX_PATH];
static OPENFILENAME ofn;

void PopFileInitializeX(HWND hwnd)
{
    static TCHAR szFilter[1024] = /*TEXT("CommandCube扩展程序(*.cxlib , *.clib) \0"); */ TEXT("扩展程序(*.cxlib)\0*.cxlib\0"); \

        ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.hInstance = NULL;
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0;
    ofn.nFilterIndex = 0;
    ofn.lpstrFile = szFileName;          // Set in Open and Close functions
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFileTitle = NULL;          // Set in Open and Close functions
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = NULL;
    ofn.Flags = 0;             // Set in Open and Close functions
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = TEXT("cxlib");
    ofn.lCustData = 0L;
    ofn.lpfnHook = NULL;
    ofn.lpTemplateName = NULL;
    /*
    if (GetOpenFileName(&ofn))
    {
        MessageBox(hwnd, ofn.lpstrFile, ofn.lpstrFile, 0);
    }
    */
}

BOOL PopFileOpenDlgX(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = pstrFileName;
    ofn.lpstrFileTitle = pstrTitleName;
    ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

    return GetOpenFileName(&ofn);
}
HINSTANCE UIHINST;
HWND hext;
WNDPROC EXTTOLD;
typedef struct tagEXT
{// 
    HWND hWnd;          // handle of owner window
    BOOL x1; //默认是185
    BOOL y1; //默认是170
    BOOL x2;
    BOOL y2;
    HBRUSH style;
    UINT        styleU;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    LPCWSTR     lpszMenuName;
    LPCWSTR     lpszClassName;
} EXT_PARAM;
//static wchar_t m_strInput[0xfffff] = L""; //声明输入框变量
#define IDS_TEXT1 0x200
#define IDB_BT1 0x199
BOOL CALLBACK EXTUIProc(HWND hEXT, UINT message, WPARAM wParam, LPARAM lParam) //str=wcs,必须转化成Unicode
{

    PAINTSTRUCT ps = { 0 };
    HDC DC = NULL;
    RECT rect;
    GetClientRect(hEXT,&rect);
    //    RECT rc;
    //    char prompt[40];
    //int len = wcslen(m_strInput);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        Text(hEXT, 50, 40, L"扩展程序可以为CommandCube提供外接功能.");
        ButtonEx(hEXT, 70, 100,130,30, L"加载扩展", IDB_BT1);
        break;
    }
    break;
    case WM_PAINT:
    {
        HDC hdc = NULL;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hEXT, &ps);
        HBRUSH hbr = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hdc,&rect,hbr);
        ReleaseDC(hEXT, hdc);
        EndPaint(hEXT, &ps);
        break;
    }
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDB_BT1:
        {
            PopFileInitializeX(hEXT);  //初始化ofn
            PopFileOpenDlgX(hEXT, szFileName, szTitleName);//打开文件对话框
            HZIP hz = OpenZip(szFileName, 0);
            ZIPENTRY ze; GetZipItem(hz, -1, &ze); int numitems = ze.index;
            //赋值
            for (int zi = 0; zi < numitems; zi++)
            {
                if (!access("C://CommandCube//temp", 0))
                {

                    ZIPENTRY ze; GetZipItem(hz, zi, &ze); // 启动解压API
                    SetUnzipBaseDir(hz, L"C:\\CommandCube\\temp\\");
                    UnzipItem(hz, zi, ze.name);         // 名字
                }
                else
                {
                    mkdirs("C:/CommandCube/temp");
                    ZIPENTRY ze; GetZipItem(hz, zi, &ze); // 启动解压API
                    SetUnzipBaseDir(hz, L"C:\\CommandCube\\temp\\");
                    UnzipItem(hz, zi, ze.name);         // 名字
                }

            }
            if (hz)
            {
                if (!access("C://CommandCube//temp//manifest.cxdata", 0))
                {
                    char buffer[1024];
                    char bufferB[1024];
                    OPENTEXT("C:\\CommandCube\\temp\\manifest.cxdata",buffer);
                    OPENTEXT("C:\\CommandCube\\temp\\manifest.cxdata", bufferB);
                    char PathDir[80] = "C:\\CommandCube\\temp\\";
                    char PathDirB[80] = "C://CommandCube//temp//";
                    strcat(PathDir,buffer);
                    strcat(PathDirB, bufferB);
                    MessageBoxA(NULL, bufferB, "", NULL);
                    if (!access(/*"C://CommandCube//temp//main.exe"*/bufferB, 0))
                    {
                        system(/*"C:\\CommandCube\\temp\\main.exe"*/buffer);
                    }
                    else
                    {
                        TipBox(NULL, L"成功获取清单,但不能找到入口点.\n[入口点缺失]", L"入口点错误", 0);
                    }
                    delete[] buffer;
                }
                else
                {
                    TipBox(NULL, L"扩展程序未能加载,因为不能找到清单文件.\n[入口点错误]", L"入口点错误", 0);
                }
            }
            if (!hz)
            {
                break;
            }
            CloseZip(hz);
            break;
        }
        }
        break;
    }
    case WM_CLOSE:
    {
        /*
        int         iRC = 0;
        std::wstring strDirectoryToDelete = L"c:\\CommandCube";
        iRC = DeleteDirectory(strDirectoryToDelete);
        // Wait for keystroke
        _getch();
        if (iRC)
        {
            ActBox(NULL, L"清空缓存时遇到未知错误.(QAQ)\n\n请先关闭当前扩展程序,之后进入设置->清除缓存.", L"...", NULL);
        }
        */
        EndDialog(hEXT, 0);
        break;
    }
    break;
    default: 
        break;
    }
    return FALSE;
}

int  EXTUI(
    HWND hWnd       // handle of owner window
    //BOOL x1,
    //BOOL y1,
    //BOOL x2,
    //BOOL y2,
    //LPWSTR in,
    //int Cmd
)
{
    static HFONT hFont;
    UIHINST = hInstance;
    WNDCLASS wnc;
    
    EXT_PARAM btn = { 0 };
    btn.hWnd = hWnd;
    

    // hconsole = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_CONSOLE), hWnd, ConsoleUIProc);

    DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
        MAKEINTRESOURCE(IDD_EXT), NULL, EXTUIProc, (LPARAM)&btn);
    //MoveWindow()
    //AnimateWindow(hconsole, 300, AW_BLEND | Cmd);
    //EXTTOLD = (WNDPROC)SetWindowLong(hext, GWL_WNDPROC, (LONG)EXTUIProc);
    //ShowWindow(hext, Cmd);

    return -1;
}