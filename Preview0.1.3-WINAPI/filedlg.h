#pragma once
#include <Windows.h>
#include <CommDlg.h>
#include <iostream>

//#define MAX_LOADSTRING 100 
// using namespace std;
static TCHAR     szFileName1[MAX_PATH], szTitleName1[MAX_PATH];
static OPENFILENAME ofn;

void PopFileInitialize(HWND hwnd)
{
    static TCHAR szFilter[1024] = /*TEXT("CommandCube扩展程序(*.cxlib , *.clib) \0"); */ TEXT("扩展程序(*.cxlib)\0*.cxlib\0"); \

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.hInstance = NULL;
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0;
    ofn.nFilterIndex = 0;
    ofn.lpstrFile = szFileName1;          // Set in Open and Close functions
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

BOOL PopFileOpenDlg(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = pstrFileName;
    ofn.lpstrFileTitle = pstrTitleName;
    ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

    return GetOpenFileName(&ofn);
}

        //PopFileInitialize(hWnd);  //初始化ofn
        //PopFileOpenDlg(hWnd, szFileName, szTitleName);//打开文件对话框
