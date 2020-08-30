#pragma once
#include "framework.h"
#include "Windesktop.h"
#include "Colordef.h"
#include "UILibEx.h"
#include "UIMain.h"
#include "zip.h"
#include "unzip.h"
HINSTANCE UI_HIN;
HWND hconsole;
WNDPROC CONSOLETOLD;
typedef struct tagCON
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
} CON_PARAM;
static wchar_t m_strInput[0xfffff] = L""; //声明输入框变量
LRESULT CALLBACK ConsoleUIProc(HWND hBtn2, UINT message, WPARAM wParam, LPARAM lParam) //str=wcs,必须转化成Unicode

{
    static POINT m_CaretPos;
    static int wid = 1; /*字节宽度*/

    PAINTSTRUCT ps = { 0 };
    HDC DC = NULL;
    //    RECT rc;
    //    char prompt[40];
    int len = wcslen(m_strInput);
    switch (message)
    {
    case WM_CREATE:
    {
        //MoveWindow(hBtn2, 160, 51, 835, 512, TRUE);
        //
        SetFocus(hBtn2);
        ::CreateCaret(hBtn2, NULL, 1, 18);
        m_CaretPos.x = 2;// 1 pxl bigger
        m_CaretPos.y = 2;
        ::SetCaretPos(m_CaretPos.x, m_CaretPos.y);
        ShowCaret(hBtn2);
        //画椭圆区域，还可以画圆角，多边形等等
        /*
        HRGN hRgn = CreateRoundRectRgn(0, 0, 251, 39, 3, 10);
        SetWindowRgn(hBtn2, hRgn, TRUE);
        */
        break;
    }
    break;
    case WM_LBUTTONDOWN:
    {
        //
        SetFocus(hBtn2);
        ::CreateCaret(hBtn2, NULL, 1, 18);
        ShowCaret(hBtn2);
        break;
    }
    case WM_PAINT: //设置文本特定内容的颜色
    {
        HBRUSH br = CreateSolidBrush(RGB(189, 195, 199));
        HBRUSH gbr = CreateSolidBrush(GOON);
        if (wcsncmp(m_strInput, L"-", 1) == 0)
        {
            DC = BeginPaint(hBtn2, &ps);
            FillRect(DC, &ps.rcPaint, gbr);
            SetBkColor(DC, RGB(53, 56, 88));
            SetTextColor(DC, RGB(160, 223, 59));
            TextOut(DC, 1, 2, m_strInput, wcslen(m_strInput));
            //more left 1 than m_CaretPos.x=2
            EndPaint(hBtn2, &ps);
        }
        if (wcsncmp(m_strInput, L"build", 5) == 0)
        {
            DC = BeginPaint(hBtn2, &ps);
            SetBkColor(DC, RGB(53, 56, 68));
            SetTextColor(DC, RGB(39, 169, 234));
            TextOut(DC, 1, 2, m_strInput, wcslen(m_strInput));
            //more left 1 than m_CaretPos.x=2
            EndPaint(hBtn2, &ps);
        }
        if (wcsncmp(m_strInput, L"gen", 3) == 0)
        {
            DC = BeginPaint(hBtn2, &ps);
            SetBkColor(DC, RGB(53, 56, 68));
            SetTextColor(DC, RGB(192, 144, 244));
            TextOut(DC, 1, 2, m_strInput, wcslen(m_strInput));
            //more left 1 than m_CaretPos.x=2
            EndPaint(hBtn2, &ps);
        }
        if (wcsncmp(m_strInput, L"test", 4) == 0)
        {
            HFONT hFont = 0;
            LOGFONT lf;
            DC = BeginPaint(hBtn2, &ps);
            SetBkColor(DC, RGB(53, 56, 68));
            SetTextColor(DC, RGB(255, 128, 128));
            if (hFont == 0)
            {
                memset(&lf, 0, sizeof(LOGFONT));
                lf.lfHeight = -16;
                wcscpy(lf.lfFaceName, L"Segoe UI");
                hFont = CreateFontIndirect(&lf);  // create the font
            }
            HFONT old = (HFONT)SelectObject(DC, hFont);
            TextOut(DC, 0, 2, m_strInput, wcslen(m_strInput));
            //more left 1 than m_CaretPos.x=2
            EndPaint(hBtn2, &ps);
        }
        else
        {
            DC = BeginPaint(hBtn2, &ps);
            FillRect(DC, &ps.rcPaint, br);
            SetBkColor(DC, RGB(53, 56, 68));
            SetTextColor(DC, RGB(67, 166, 66));
            TextOut(DC, 1, 2, m_strInput, wcslen(m_strInput));
            //more left 1 than m_CaretPos.x=2
            EndPaint(hBtn2, &ps);
        }
    }
    break;
    case WM_SETFOCUS:
        
        ShowCaret(hBtn2);
        break;
    case WM_KILLFOCUS:
        HideCaret(hBtn2);
        break;
    case WM_CHAR:
    {
        DC = GetDC(hBtn2);
        if ((wchar_t)wParam == 0x0D)
        {
            OutputDebugString(L"input finish !");
            return 0;
        }
        if ((wchar_t)wParam == 8) // backpace
        {
            if (len > 0)
            {
                if ((BYTE)m_strInput[len - 2] >= 0x80)
                {// CN TXT
                    GetCharWidth(DC, 'LL', 'LL', &wid);// =10
                    m_strInput[len - 1] = 0;
                    len--;
                    m_strInput[len - 1] = 0;
                    m_CaretPos.x -= 2 * wid;
                }
                else
                {
                    //GetCharWidth(DC, 'LL', 'LL', &wid);// =10
                    GetCharWidth(DC, m_strInput[len - 1], m_strInput[len - 1], &wid);
                    m_strInput[len - 1] = 0;
                    m_CaretPos.x -= wid;
                }
            }
        }
        else
        {
            if ((BYTE)wParam >= 0x80)
            {// 汉字
                GetCharWidth(DC, 'LL', 'LL', &wid);// W=15 L=10
                //                sprintf(prompt,"%d\n",wid);
                //                OutputDebugString(prompt);
            }
            else
            {
                GetCharWidth(DC, wParam, wParam, &wid);
            }
            // not strcat !
            m_strInput[len] = wParam;
            m_strInput[len + 1] = 0;
            m_CaretPos.x += wid;
        }
        SetCaretPos(m_CaretPos.x, m_CaretPos.y);
        // all !!
        InvalidateRect(hBtn2, 0, TRUE);
        break;
    }
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case 0x25:
        {
            if (m_CaretPos.x > 2)
            {
                int w = 10;
                //GetCharWidth32(DC,'L','L',&w);// W=15 L=10
                m_CaretPos.x -= w;
                SetCaretPos(m_CaretPos.x, m_CaretPos.y);
            }
            break;
        }
        case VK_RIGHT:
        {
            if (m_CaretPos.x < 200)
            {
                int w = 10;
                //GetCharWidth32(DC,'L','L',&w);// W=15 L=10
                m_CaretPos.x += w;
                SetCaretPos(m_CaretPos.x, m_CaretPos.y);
            }
            break;
        }
        case VK_RETURN:
        {
            //指向UUID生成---------------------------------------------------------------------------------
            if (wcsncmp(m_strInput, L"gen uuid", 11) == 0) // same
            {
                genuuid();
                return 0;
            }
            // CREATE uuid in txt-----------------------------------------------------------------------
            if (wcsncmp(m_strInput, L"build uuid in txt", 14) == 0) // same
            {
                CreateUUID();
                return 0;
            }
            //build manifest----------------------------------------------------------------------------
            if (wcsncmp(m_strInput, L"build manifest", 14) == 0)
            {
                bdmanifest();
                return 0;
            }
            //CreateMCPACK floder--------------------------------------------------------------------------------
            if (wcsncmp(m_strInput, L"build respack", 14) == 0)
            {
                buildres();
                return 0;
            }
            ///THEME---------------------------------------------------------------------------------------------
            if (wcsncmp(m_strInput, L"settheme light", 15) == 0)
            {
                ActBox(NULL, L"意外的错误[0x114514]", L"无法执行命令", 0);
                break;
            }
            //----------------------------------------------------------------------------------------------------
            if (wcsncmp(m_strInput, L"test", 15) == 0)
            {
                TipBox(NULL, L"TIPBOX TEST", L"TIPBOX", 0);
                ActBox(NULL, L"ACTBOX TEST", L"TEST", 0);
                FatalBox(NULL, L"FATAL QAQ", L"TEST", 0);
                GBox(NULL, L"FantasticBox", L"TEST", 0);
                break;
            }
            if (wcsncmp(m_strInput, L"test GBox", 15) == 0)
            {
                GBox(NULL, L"GBOX,IT IS A GRADIENT TITLE BAR TIPBOX!", L"GRADIENT!", 0);
                break;
            }
            if (wcsncmp(m_strInput, L"exit", 4) == 0)
            {
                PostQuitMessage(0);
                break;
            }
            if (wcsncmp(m_strInput, L"-edit", 4) == 0) // same
            {
                TextEdit(NULL, NULL, NULL, NULL);
                break;
            }
            if (wcsncmp(m_strInput, L"-sizeof", 4) == 0) // same
            {
                MessageBox(hBtn2, (LPWSTR)len, L"SizeOfInput", 0);
                break;
            }
            if (wcsncmp(m_strInput, L"-unpack", 7) == 0)
            {
                HZIP hz = OpenZip(L"pack.zip", 0);
                ZIPENTRY ze; GetZipItem(hz, -1, &ze); int numitems = ze.index;
                // -1 gives overall information about the zipfile
                for (int zi = 0; zi < numitems; zi++)
                {
                    ZIPENTRY ze; GetZipItem(hz, zi, &ze); // fetch individual details
                    UnzipItem(hz, zi, ze.name);         // e.g. the item's name.
                }
                if (hz)
                {
                    TipBox(NULL, L"成功解压了qwq", L"解压完成!", 0);
                }
                if (!hz)
                {
                    GBox(NULL, L"出现错误了QAQ\n\n当前unpack处于测试阶段,请将要解压的zip文件\n重命名为pack.zip并放置在当前CommandCube目录下.\n\n它还寄托着希望.", L"Dream", 0);
                }
                CloseZip(hz);
                break;
            }
            //help————————————————————————————————————————————————————————————————————————————————————————————————
            if (wcsncmp(m_strInput, L"help", 4) == 0) // same
            {
                ActBox(NULL, L" gen uuid -生成UUID \n\n build uuid in txt -在当前目录下将uuid写入uuid.txt \n\n build manifest -建立适用于MCPE的插件MANIFEST \n\n build respack -建立适用于MCPE的空资源包预设 \n\n", L"COMMANDLINEUI", MB_OK);
                break;
            }
            //
            //            if(.........) {;}
            else
            {
                //如果不存在
                //MessageBox(NULL, "//", "//", 0);
                CmdlBox(NULL, L"生成UUID                              ", NULL, NULL);
                break;
            }
            return 0;
        }
        }
        break;
    }
    default:
        break;
    }
    return CallWindowProc(CONSOLETOLD, hBtn2, message, wParam, lParam);

}

int ConsoleUI(
    HWND hWnd,         // handle of owner window
    BOOL x1,
    BOOL y1,
    BOOL x2,
    BOOL y2,
    //LPWSTR in,
    int Cmd
)
{
    static HFONT hFont;
    UI_HIN = hInstance;
    WNDCLASS wnc;
    CON_PARAM btn = { 0 };
    btn.hWnd = hWnd;
    
   // hconsole = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_CONSOLE), hWnd, ConsoleUIProc);
    
    hconsole = CreateWindow(L"#32770", L"ConsoleClass",
        WS_CHILD , x1, y1, x2, y2, hWnd, NULL, hInstance, 0);
    ShowWindow(hconsole, Cmd);
    //AnimateWindow(hconsole, 300, AW_BLEND | Cmd);
    CONSOLETOLD = (WNDPROC)SetWindowLong(hconsole, GWL_WNDPROC, (LONG)ConsoleUIProc);
   

    return -1;
}