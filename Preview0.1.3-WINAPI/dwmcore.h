#pragma once
#include "framework.h"
#include <windowsx.h>
#include "dwmapi.h"

HRESULT EnableBlurBehind(HWND hwnd)
{
    HRESULT hr = S_OK;

    // Create and populate the blur-behind structure.
    DWM_BLURBEHIND bb = { 1 };

    // Specify blur-behind and blur region.
    bb.dwFlags = DWM_BB_ENABLE;
    bb.fEnable = true;
    bb.hRgnBlur = NULL;

    // Enable blur-behind.
    hr = DwmEnableBlurBehindWindow(hwnd, &bb);
    if (SUCCEEDED(hr))
    {
        // ...
    }
    return hr;
}