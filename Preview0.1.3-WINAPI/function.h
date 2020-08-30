#pragma once
#include "UIMain.h"
#include <direct.h>
#include "resource.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <io.h>
#include "framework.h"
#include "CommandCube.h"
#include "dwmcore.h"
#define ACTBOX ActBox
#pragma warning(disable:4996)
using namespace::std;

void WriteJson()
{
    dpath;
    strcpy(desktop + index, "\\desktop\\manifest.json");
    FILE* fp = fopen(desktop, "wt");
    if (!fp)
    {
        ACTBOX(NULL, L"QAQ:唉，最终为什么还是没能创建文件呢?[磁盘空间不足或未获得访问权限.]\n\n点击关闭将继续尝试.", L"好像发生了什么", 0);
    }
    if (fp)
    {
        fprintf(fp,
            "{\n"
            "\"format_version\": 1,\n"
            "\"header\": {\n"
            "    \"description\": \"资源包介绍\",\n"
            "    \"name\": \"资源包展示的名称\",\n"
            "    \"uuid\": \"WWWWWWWW-XXXX-YYYY-ZZZZ-WWWWWWWWWWWW\",\n"
            "    \"version\": [0, 0, 1],//资源包版本标识\n"
            "    \"min_engine_version\": [1, 12, 0]\n"
            "},\n"
            "\"modules\": [\n"
            "    {\n"
            "        \"description\": \"resourcePack.vanilla.description\",\n"
            "        \"type\": \"resources\",\n"
            "        \"uuid\": \"53644fac-a276-42e5-843f-a3c6f169a9ab\",\n"
            "        \"version\": [0, 0, 1]\n"
            "    }\n"
            "]\n"
            "}"
        );
        fclose(fp);
    }
}
// 重写 Uuid
void SetJsonUuid(char* newJsonUuid)
{
    dpath;
    strcpy(desktop + index, "\\desktop\\manifest.json");
    FILE* fp = fopen(desktop, "rt");
    int len;
    char buf[1024];
    if (fp)
    {// read
        len = fread(buf, 1, sizeof(buf), fp);
        buf[len] = 0; // become string
        fclose(fp);
    }
    // 
    char* start;
    int sublen = strlen(newJsonUuid);
    start = strstr(buf, "WWWWWWWW-XXXX-YYYY-ZZZZ-WWWWWWWWWWWW");
    while (start)
    {
        memmove(start, newJsonUuid, sublen);
        start += sublen;
        start = strstr(buf, "WWWWWWWW-XXXX-YYYY-ZZZZ-WWWWWWWWWWWW");
    }
    //
    fp = fopen(desktop, "wt");
    if (fp)
    {// write
        fwrite(buf, 1, len, fp);
        fclose(fp);
    }
}
void mkdirs(char* muldir)
{
    int i, len;
    char str[512];
    strncpy(str, muldir, 512);
    len = strlen(str);
    for (i = 0; i < len; i++)
    {
        if (str[i] == '/')
        {
            str[i] = '\0';
            if (_access(str, 0) != 0)
            {
                _mkdir(str);
            }
            str[i] = '/';
        }
    }
    if (len > 0 && _access(str, 0) != 0)
    {
        _mkdir(str);
    }
    return;
} 
void CenterWindow(HWND hWnd)
{
    int scrWidth, scrHeight;
    RECT rect;
    //获得屏幕尺寸
    scrWidth = GetSystemMetrics(SM_CXSCREEN);
    scrHeight = GetSystemMetrics(SM_CYSCREEN);
    //取得窗口尺寸
    GetWindowRect(hWnd, &rect);
    //重新设置rect里的值  
    long width = rect.right - rect.left;
    long height = rect.bottom - rect.top;
    rect.left = (scrWidth - width) / 2;
    rect.top = (scrHeight - height) / 2;

    //移动窗口到指定的位置
    SetWindowPos(hWnd, HWND_TOP, rect.left, rect.top, width, height, SWP_NOSIZE | SWP_NOZORDER);
}
//---------------------------------------------------------就到这里了---------------------------
BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_PAINT:
    {
        HPEN hpen = CreatePen(PS_SOLID, 2, RGB(215, 122, 106));
        HPEN hpenOld = NULL;
        HDC hdc = NULL;
        HDC hdc2 = NULL;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwndDlg, &ps);
        HBRUSH br = CreateSolidBrush(RGB(60, 60, 60));
        FillRect(hdc, &ps.rcPaint, br);
        //SelectObject(hdc, hpen);
        //SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
        //Rectangle(hdc, 0, 0, 174, 193);
        TRIVERTEX vert[2];

        GRADIENT_RECT gRect;



        vert[0].x = 0;

        vert[0].y = 0;

        vert[0].Red = 0x0000;

        vert[0].Green = 0xfff0;

        vert[0].Blue = 0xff00;

        vert[0].Alpha = 0x0000;



        vert[1].x = 483;

        vert[1].y = 20;

        vert[1].Red = 0x0f00;

        vert[1].Green = 0xac00;

        vert[1].Blue = 0xffa0;

        vert[1].Alpha = 0x0000;



        gRect.UpperLeft = 0;

        gRect.LowerRight = 1;



        GradientFill(hdc, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
        ReleaseDC(hwndDlg, hdc);//Over                                             // 12
        EndPaint(hwndDlg, &ps);
        DeleteObject(br);
        //EnableBlurBehind(hwndDlg);
        return TRUE;
    }
    case WM_INITDIALOG:
        SetWindowTextA(GetDlgItem(hwndDlg, IDC_EDIT2), (char*)lParam);
        Button(hwndDlg, 360, 120, L"关闭",IDC_BUTT);
        return TRUE;
    case WM_CLOSE:
        EndDialog(hwndDlg, 0);
        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BUTT || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hwndDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    }
    return FALSE;
}
//---------------------------------------------------------------------------------------------
void CreateUUID()
{
    const char* uuidtest = "start notepad %userprofile%/desktop/uuid.txt";
    dpath;
    strcpy(desktop + index, "\\desktop\\uuid.txt");
    UUID uuid;
    UuidCreate(&uuid);
    /*
    UUID uuid2;
    UuidCreate(&uuid2);
    UUID uuid3;
    UuidCreate(&uuid3);
    */
    unsigned char* str = (unsigned char*)malloc(256);
    UuidToStringA(&uuid, &str);
    FILE* fp = fopen(desktop, "wt");
    if (!fp)
    {
        ACTBOX(NULL, L"QAQ:唉，最终为什么还是没能创建文件呢?[磁盘空间不足或未获得访问权限.]\n\n点击关闭将继续尝试.", L"好像发生了什么", 0);
    }
    if (fp)
    {
        fprintf(fp,
            "%s",
            str
        );
        fclose(fp);
    }
    RpcStringFreeA(&str);
    TipBox(NULL, L"UUID 已成功创建于uuid.txt中", L"COMPLETE", 0);
    system(uuidtest);
}
void bdmanifest()
{
    const char* manifest_d = "start notepad %userprofile%/desktop/manifest.json";
    dpath;
    strcpy(desktop + index, "\\desktop\\manifest.json");
    UUID uuid;
    UuidCreate(&uuid);
    unsigned char* str = (unsigned char*)malloc(256);
    UuidToStringA(&uuid, &str);
    system("del desktop\manifest.json");
    //在这里打开一个manifest.json，没有则建造，存在则替换
    WriteJson();
    SetJsonUuid((char*)str);
    RpcStringFreeA(&str);
    GBox(NULL, L"MANIFEST.JSON （用于MCBE资源包）建造已结束！\n[默认放置于桌面]。\n\n UUID已经自动重新构建，请勿再次修改！", L"manifest build", 0);
    system(manifest_d);
}
void buildres()
{
    mkdirs("NewResPack/textures");
    mkdirs("NewResPack/shaders");
    mkdirs("NewResPack/particles");
    mkdirs("NewResPack/sounds");
    mkdirs("NewResPack/materials");
    mkdirs("NewResPack/ui");
    mkdirs("NewResPack/entity");
    mkdirs("NewResPack/models");
    mkdirs("NewResPack/texts");
    mkdirs("NewResPack/textures/ui");
    mkdirs("NewResPack/textures/blocks");
    mkdirs("NewResPack/textures/colormap");
    mkdirs("NewResPack/textures/entity");
    mkdirs("NewResPack/textures/gui");
    mkdirs("NewResPack/textures/item");
    mkdirs("NewResPack/textures/items");
    mkdirs("NewResPack/textures/models/armor");
    mkdirs("NewResPack/textures/painting");
    mkdirs("NewResPack/textures/map");
    mkdirs("NewResPack/textures/misc");
    mkdirs("NewResPack/textures/particle");
    mkdirs("NewResPack/textures/environment");
    system("start NewResPack");
    GBox(NULL, L"一个资源包已创建", L"COMPLETE", 0);
}

void genuuid()
{
    UUID uuid;
    UuidCreate(&uuid);
    unsigned char* str = (unsigned char*)malloc(256);
    UuidToStringA(&uuid, &str);
    DialogBoxParam((HINSTANCE)GetWindowLong(NULL, GWL_HINSTANCE),
        MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc, (LPARAM)(int*)str);
    RpcStringFreeA(&str);
}
