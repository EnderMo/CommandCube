#pragma once

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <windows.h>
#include <urlmon.h>
#include <Wininet.h>

#define MAX_THREADS 2 
//#pragma comment(lib,"Urlmon.lib")

//#pragma comment(lib, "Wininet.lib")

using namespace std;
/*
BOOL FileExistsStatus(const CHAR* path)
{
    DWORD dwAttribute = GetFileAttributes(path);
    if (dwAttribute == 0XFFFFFFFF) return false; //0XFFFFFFFF表示文件不存在
    else return true;
}

BOOL DownloadFiles(LPCSTR url, LPCSTR downloadPath)
{
    if (URLDownloadToFile(NULL, url, downloadPath, 0, 0) == S_OK && FileExistsStatus(downloadPath)) return true;
    else return false;
}

void update(int argc, char* argv[])
{
    if (DownloadFiles(argv[1], argv[2])) printf("OK!\n");
    else printf("Error!\n");
    //return 0;
}
*/
#include <stdio.h>
#include <Urlmon.h>
#include <Wininet.h>

#pragma comment(lib,"Urlmon.lib")

#pragma comment(lib, "Wininet.lib")

#include "function.h"
#include "CommandCube.h"
#define cdir "cd C:/CommandCube/Downloads\n"

void bdupdater()
{
    char szFilePathN[MAX_PATH + 1] = { 0 };
    GetModuleFileNameA(NULL, szFilePathN, MAX_PATH);//保留文件名
    char szFilePath[MAX_PATH + 1] = { 0 };
    GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
    (strrchr(szFilePath, _T('\\')))[1] = 0; // 删除文件名，只获得路径字串
    FILE* fp = fopen("C:\\CommandCube\\Downloads\\go.cmd", "wt");
    if (!fp)
    {
        ACTBOX(NULL, L"创建更新数据库失败.[磁盘空间不足或未获得访问权限.]", L"好像发生了什么", 0);
    }
    if (fp)
    {
        fputs("@echo off \n", fp);
        fputs("taskkill /f /im CommandCube.exe\n", fp);
        fputs(cdir, fp);
        fputs("echo CommandCube正在更新中. \n", fp);
        fputs("del ", fp);
        fputs(szFilePathN, fp);
        fputs("\ncls\n", fp);
        fputs("echo CommandCube正在完成更新[1/1]... \n", fp);
        fputs("\ncopy CommandCube.exe ", fp);
        fputs(szFilePath, fp);
        fputs("\n", fp);
        fputs("start ", fp);
        fputs(szFilePathN, fp);
        fputs("\n", fp);
        fclose(fp);
    }
}

#define IDC_YES_DOWN 0x00FF2
#define IDC_NO_CLOSE 0x00FF3
//---------------
typedef struct tagMMBEX
{// 
    HWND hWnd;          // handle 

    LPCSTR lpText;     // text 

    LPCTSTR lpCaption;  //  title 

    UINT uType;         // style 

} MMB_PARAMEX;
//
BOOL CALLBACK DialogProc1EX(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
    MMB_PARAMEX* pmmb = (MMB_PARAMEX*)lParam;
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetWindowText(hwndDlg, pmmb->lpCaption);
        SetWindowTextA(GetDlgItem(hwndDlg, IDC_STATIC), pmmb->lpText);
        //222222
        Button(hwndDlg, 135, 170, L"关闭",IDC_NO_CLOSE);
        Button(hwndDlg, 265, 170, L"下载", IDC_YES_DOWN);
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
        RoundRect(hdc, 420, 25, 440, 5, 1, 1);
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
        switch (LOWORD(wParam))
        {
        case IDC_YES_DOWN:
        {
            CoInitialize(NULL);
            wchar_t* pURL = L"https://api.endermo.xyz/Update/CommandCube.exe";
            wchar_t* pFileName = L"C:\\CommandCube\\Downloads\\CommandCube.exe";
            char szBuffer[1024 * 128] = { 0 };
            unsigned long iSize = 0;
            char szPreCommand[128] = { 0 };
            DeleteUrlCacheEntry(pURL);//清空缓存，否则服务器上的文件修改后，无法下载最新的文件
            if (URLDownloadToFile(NULL, pURL, pFileName, 0, NULL) == S_OK)
            {
                bdupdater();
                EndDialog(hwndDlg, 0);
                MessageBox(hwndDlg, L"更新已经就绪.点击'确定'安装更新.", L"NewVersion", 0);
                system("C:/CommandCube/Downloads/go.cmd");
            }
            else
            {
                EndDialog(hwndDlg, 0);
                ActBox(NULL, L"[QAQ]下载更新时出现了错误!\n\nERROR_CODE_TIMEOUT", L"NULL", 0);
            }
            CoUninitialize();
            break;
        }
        case IDC_NO_CLOSE:
        {
            EndDialog(hwndDlg, 0);
            break;
        }
        }
    case WM_CLOSE:
        EndDialog(hwndDlg, 0);
    }
    }
    return FALSE;
}
//
int VerBoxEx(
    HWND hWnd,          // handle 
    LPCSTR lpText,     // text 
    LPCTSTR lpCaption,  // title 
    WORD uType          // style 
)
{
    MMB_PARAMEX mmb;
    mmb.hWnd = hWnd;
    mmb.lpText = lpText;
    mmb.lpCaption = lpCaption;
    mmb.uType = uType;
    DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
        MAKEINTRESOURCE(IDD_TIPBOX), NULL, DialogProc1EX, (LPARAM)&mmb);
    return -1;
}
//----------------
#define VerstrA char VerA[80]="当前版本:";\
 char verNumA[] = verA;\
 strcat(VerA, verNumA);
void C_update()
{
    CoInitialize(NULL);
    mkdirs("C:/CommandCube");
    mkdirs("C:/CommandCube/Downloads");
    FILE* fp = fopen("C:\\CommandCube\\ver.txt", "wt");
    if (!fp)
    {
        ACTBOX(NULL, L"QAQ:唉，最终为什么还是没能创建文件呢?[磁盘空间不足或未获得访问权限.]\n\n点击关闭将继续尝试.", L"好像发生了什么", 0);
    }
    if (fp)
    {
        fprintf(fp,
            verA
               );
        fclose(fp);
    }
    //PopBox(NULL, "正在获取更新...", "CommandCubeVersionSelector", 0);
    wchar_t* pURL = L"https://api.endermo.xyz/Update/update.txt";
    wchar_t* pFileName = L"C:\\CommandCube\\Update.txt";
    char szBuffer[1024 * 128] = { 0 };
    unsigned long iSize = 0;
    char szPreCommand[128] = { 0 };
    DeleteUrlCacheEntry(pURL);//清空缓存，否则服务器上的文件修改后，无法下载最新的文件
    if (URLDownloadToFile(NULL, pURL, pFileName, 0, NULL) == S_OK)
    {
        filebuf* pbuf;

        ifstream filestr;

        long size;

        char* buffer;

        filestr.open("c:\\CommandCube\\Update.txt", ios::in | ios::binary);

        pbuf = filestr.rdbuf();

        size = pbuf->pubseekoff(0, ios::end, ios::in);

        pbuf->pubseekpos(0, ios::in);

        buffer = new char[size];

        pbuf->sgetn(buffer, size);

        filestr.close();

        VerstrA;
        strcat(VerA, "\n\n最新版本:");
        strcat(VerA, buffer);
        VerBoxEx(NULL, VerA, L"NewVersion", NULL);

        delete[] buffer;

    }
    else
    {
       ActBox(NULL,L"[QAQ]检查更新时出现了错误!\n\nERROR_CODE_TIMEOUT",L"NULL",0);
    }
    CoUninitialize();
}
