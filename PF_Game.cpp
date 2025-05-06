#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void ShowWelcome(HWND);
void ClearWindow(HWND);

enum PageState { WELCOME};
enum PageState currentPage = WELCOME;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "SignupWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("SignupWindow", "Sign Up", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 600, 600, NULL, NULL, hInstance, NULL);
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
	
	ShowWelcome(hwnd);
	
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void ShowWelcome(HWND hwnd) {
    ClearWindow(hwnd);
    CreateWindow("STATIC", "Welcome! Choose an option:", WS_VISIBLE | WS_CHILD, 180, 100, 250, 30, hwnd, NULL, NULL, NULL);
    CreateWindow("BUTTON", "Signup", WS_VISIBLE | WS_CHILD, 200, 150, 180, 30, hwnd, (HMENU)1, NULL, NULL);
    CreateWindow("BUTTON", "Login", WS_VISIBLE | WS_CHILD, 200, 200, 180, 30, hwnd, (HMENU)2, NULL, NULL);
    currentPage = WELCOME;
}

void ClearWindow(HWND hwnd) {
    HWND child = GetWindow(hwnd, GW_CHILD);
    while (child) {
        DestroyWindow(child);
        child = GetWindow(hwnd, GW_CHILD);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
