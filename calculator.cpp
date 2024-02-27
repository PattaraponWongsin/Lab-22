#ifndef UNICODE
#define UNICODE
#endif 
#include <windows.h>
#include <string>
#define MAX_STR_ALLOC 255

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND instruction_hint;
HWND inputfield_a;
HWND inputfield_b;
HWND add_btn;
HWND sub_btn;
HWND mul_btn;
HWND div_btn;

wchar_t inputraw_a[MAX_STR_ALLOC];
wchar_t inputraw_b[MAX_STR_ALLOC];
double result;
wchar_t text_result[MAX_STR_ALLOC];

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"My Calculator";
    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 64, 128));

    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(
        0,                               
        CLASS_NAME,                     
        L"My Calculator",    
        WS_SYSMENU,                     
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200,
        NULL,           
        NULL,       
        hInstance,  
        NULL        
    );

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_CREATE:
        instruction_hint = CreateWindow(
            L"STATIC",
            L"Please input two numbers",
            WS_VISIBLE | WS_CHILD,
            15, 15, 185, 18,
            hwnd, NULL, NULL, NULL
        );
        inputfield_a = CreateWindow(
            L"EDIT",
            L"",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            20, 35, 185, 18,
            hwnd, NULL, NULL, NULL
        );
        inputfield_b = CreateWindow(
            L"EDIT",
            L"",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            20, 58, 185, 18,
            hwnd, NULL, NULL, NULL
        );

        add_btn = CreateWindow(
            L"BUTTON",
            L"+",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            50, 81, 25, 25,
            hwnd,
            (HMENU)100, NULL, NULL
        );
        sub_btn = CreateWindow(
            L"BUTTON",
            L"-",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            80, 81, 25, 25,
            hwnd,
            (HMENU)101, NULL, NULL
        );
        mul_btn = CreateWindow(
            L"BUTTON",
            L"*",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            110, 81, 25, 25,
            hwnd,
            (HMENU)102, NULL, NULL
        );
        div_btn = CreateWindow(
            L"BUTTON",
            L"/",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            140, 81, 25, 25,
            hwnd,
            (HMENU)103, NULL, NULL
        );
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 100:
            GetWindowText(inputfield_a, inputraw_a, MAX_STR_ALLOC);
            GetWindowText(inputfield_b, inputraw_b, MAX_STR_ALLOC);
            result = _wtof(inputraw_a) + _wtof(inputraw_b);
            swprintf_s(text_result, L"%lf", result);
            MessageBox(hwnd, text_result, L"Result", MB_OK);
            break;
        case 101:
            GetWindowText(inputfield_a, inputraw_a, MAX_STR_ALLOC);
            GetWindowText(inputfield_b, inputraw_b, MAX_STR_ALLOC);
            result = _wtof(inputraw_a) - _wtof(inputraw_b);
            swprintf_s(text_result, L"%lf", result);
            MessageBox(hwnd, text_result, L"Result", MB_OK);
            break;
        case 102:
            GetWindowText(inputfield_a, inputraw_a, MAX_STR_ALLOC);
            GetWindowText(inputfield_b, inputraw_b, MAX_STR_ALLOC);
            result = _wtof(inputraw_a) * _wtof(inputraw_b);
            swprintf_s(text_result, L"%lf", result);
            MessageBox(hwnd, text_result, L"Result", MB_OK);
            break;
        case 103:
            GetWindowText(inputfield_a, inputraw_a, MAX_STR_ALLOC);
            GetWindowText(inputfield_b, inputraw_b, MAX_STR_ALLOC);
            result = _wtof(inputraw_a) / _wtof(inputraw_b);
            swprintf_s(text_result, L"%lf", result);
            MessageBox(hwnd, text_result, L"Result", MB_OK);
            break;
        }
        return 0;
    case WM_CTLCOLORBTN: 
        return (LRESULT)GetStockObject(WHITE_BRUSH); 
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}