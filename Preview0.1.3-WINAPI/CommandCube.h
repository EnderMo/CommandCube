#pragma once

//CommandCube.h �ṩCommandCube�ں���Ϣ

#include "resource.h"

//----VER---------------------------------

#define correct_version L"0.1.1333"

#define ver L"Preview0.1.3"

#define verA "Preview0.1.3"

//----------------------------------------
#include "framework.h"

#include "UIMain.h"





























//#define Verstr wcscpy(ver, L"�汾:"); wcscat(Ver, ver);
#define Verstr wchar_t Ver[80]=L"�汾:";\
 wchar_t verNum[] = ver;\
 wcscat(Ver, verNum);


#define dpath char desktop[MAX_PATH]; int index = GetEnvironmentVariableA("userprofile", desktop, MAX_PATH);

