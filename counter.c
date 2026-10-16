#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include <stdio.h>

#define ID_BTN_COUNT 101
#define ID_BTN_RESET 102

static int g_count = 0;
static HWND g_hLabel = NULL;

void increment_count(void) {
    g_count++;
}

void reset_count(void) {
    g_count = 0;
}

int get_count(void) {
    return g_count;
}

void update_label_text(void) {
    if (g_hLabel != NULL) {
        wchar_t buf[64];
        swprintf(buf, 64, L"カウント: %d", g_count);
        SetWindowTextW(g_hLabel, buf);
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        g_hLabel = CreateWindowExW(
            0, L"STATIC", L"カウント: 0",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            30, 20, 240, 30,
            hwnd, (HMENU)NULL, GetModuleHandle(NULL), NULL
        );

        CreateWindowExW(
            0, L"BUTTON", L"カウント",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            40, 70, 100, 35,
            hwnd, (HMENU)ID_BTN_COUNT, GetModuleHandle(NULL), NULL
        );

        CreateWindowExW(
            0, L"BUTTON", L"リセット",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            160, 70, 100, 35,
            hwnd, (HMENU)ID_BTN_RESET, GetModuleHandle(NULL), NULL
        );
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BTN_COUNT) {
            increment_count();
            update_label_text();
        } else if (LOWORD(wParam) == ID_BTN_RESET) {
            reset_count();
            update_label_text();
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"CounterWindowClass";

    WNDCLASSW wc = {0};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"カウントアプリ",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 315, 175,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
