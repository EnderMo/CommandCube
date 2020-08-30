#pragma once
#include "framework.h"
#include <shlobj.h>

#include "UIMain.h"
#include "resource2.h"

#include "gdicore.h"
int DlgClose2(HWND hwndDlg, LPARAM lParam)
{
    POINT pt;
    wchar_t txt[80];
    pt.x = LOWORD(lParam);
    pt.y = HIWORD(lParam);
    wsprintf(txt, L"x=%d;y=%d\n", LOWORD(lParam), HIWORD(lParam));
    OutputDebugString(txt);
    RECT  rc = { 435, 5, 465, 25 };// ���� bmp �������ڵ�λ�� ��
    if (PtInRect(&rc, pt))
    {
        return WM_CLOSE;
    }
    return -1;
}
#include "core.h"
typedef struct tagSETT
{// 
    HWND hWnd;          // handle 

    LPWSTR lpText;     // text 

    LPWSTR lpCaption;  //  title 

    UINT uType;         // style 

} SETT_PARAM;
//
BOOL CALLBACK SETTProc1(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HBITMAP hBitmap;                  // 1 ��̬����
    static HBITMAP hBitmap2;
    static HBITMAP hBitmap3;
    static HFONT hFont;//���徲̬�������
    BITMAP         bitmap;
    static HWND close;
    HDC hdcMem = NULL;
    static int      bmWidth, bmHeight;       // 2 ��̬����
    char txt[40];
    MMB_PARAM* pmmb = (MMB_PARAM*)lParam;
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetWindowText(hwndDlg, pmmb->lpCaption);
        SetWindowText(GetDlgItem(hwndDlg, IDC_STATIC), pmmb->lpText);
        //222222
        Button(hwndDlg, 380, 240, L"�ر�",IDC_BUTT);
        Text(hwndDlg, 10, 0, L"����");
        return TRUE;
    case WM_PAINT:
    {
        HPEN hpen = CreatePen(PS_SOLID, 2, RGB(35, 35, 35));
        HBRUSH br2 = CreateSolidBrush(RGB(0, 122, 204));
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
        Rectangle(hdc, 0, 0, 490, 30);
        //----------------close
        SelectObject(hdc, hpen3);
        SelectObject(hdc, br4);
        MoveToEx(hdc, 447, 22, NULL);
        LineTo(hdc, 462, 7);
        MoveToEx(hdc, 462, 22, NULL);
        LineTo(hdc, 447, 7);
        //----------------
        ReleaseDC(hwndDlg, hdc);//Over                                             // 12
        EndPaint(hwndDlg, &ps);
        DeleteObject(br2);
        DeleteObject(br);
        HRGN hRgn = NULL;
        RECT rect;
        GetClientRect(hwndDlg, &rect);
        hRgn = CreateRoundRectRgn(0, 0, rect.right - rect.left, rect.bottom - rect.top, 6, 6);
        SetWindowRgn(hwndDlg/*���ھ��*/, hRgn, TRUE);
        return TRUE;
    }
    case WM_CTLCOLORSTATIC:
    {
        if ((HWND)lParam == GetDlgItem(hwndDlg, IDC_STATIC))//2
        {
            SetTextColor((HDC)wParam, RGB(210, 210, 210));
            SetBkMode((HDC)wParam, TRANSPARENT);
        }
        return (INT_PTR)GetStockObject((NULL_BRUSH));//����һ���ջ�ˢ(����)
    }
    case WM_SIZE: //��Ч����Ҫ���ڵĴ���
    {
        LONG_PTR Style = ::GetWindowLongPtr(hwndDlg, GWL_STYLE);
        Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
        ::SetWindowLongPtr(hwndDlg, GWL_STYLE, Style);
        return TRUE;
    }
    case WM_LBUTTONDOWN:
    {
        if (DlgClose2(hwndDlg, lParam) > 0)
        {
            EndDialog(hwndDlg, 0);
            break;
        }
        // �ƶ����� 
        SendMessage(hwndDlg, WM_NCLBUTTONDOWN, HTCAPTION, 0);  //�򴰿ڷ���WM_NCLBUTTONDOWN��Ϣ��HTCAPTION ����
        break;
    }
    case WM_COMMAND:
    {
    case IDC_BUTT:
    {
        EndDialog(hwndDlg, 0);
    }
        UINT uNotify = HIWORD(wParam);
        if (uNotify == BN_CLICKED)
        {
            switch (LOWORD(wParam))
            {
            case IDC_BUTTON2:
            {
                int         iRC = 0;
                std::wstring strDirectoryToDelete = L"c:\\CommandCube";
                iRC = DeleteDirectory(strDirectoryToDelete);
                // Wait for keystroke
                _getch();
                if (iRC)
                {
                    ActBox(hwndDlg, L"��ջ���ʱ����δ֪����.(QAQ)\n\n�Ǿ�����CommandCube������һ�°�...",L"...",NULL);
                }
                else {
                    GBox(hwndDlg, L"�����CommandCube�����ļ�", L"*", NULL);
                }
                break;
            }
            }
        }
    }
    }
    return FALSE;
}
//
int SettBox(
    HWND hWnd,          // handle 
    LPWSTR lpText,     // text 
    LPWSTR lpCaption,  // title 
    UINT uType          // style 
)
{
    SETT_PARAM mmb;
    mmb.hWnd = hWnd;
    mmb.lpText = lpText;
    mmb.lpCaption = lpCaption;
    mmb.uType = uType;
    DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
        MAKEINTRESOURCE(DLG_SETT), NULL, SETTProc1, (LPARAM)&mmb);
    return -1;
}

