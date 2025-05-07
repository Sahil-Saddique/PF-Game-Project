#include <windows.h>
#include <stdio.h>

#define MAX_INPUT 100

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void ShowWelcome(HWND), ShowSignup(HWND);
void ClearWindow(HWND), SaveUser();

enum PageState { WELCOME, SIGNUP};
enum PageState currentPage = WELCOME;

HWND hUsername, hName, hSurname, hEmail, hPhone, hPassword, hConfirmPassword;

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
    CreateWindow("BUTTON", "Login", WS_VISIBLE | WS_CHILD, 200, 200, 180, 30, hwnd, NULL, NULL, NULL);
    currentPage = WELCOME;
}

void ShowSignup(HWND hwnd) {
    ClearWindow(hwnd);
    CreateWindow("STATIC", "Username:", WS_VISIBLE | WS_CHILD, 50, 20, 100, 20, hwnd, NULL, NULL, NULL);
    	hUsername = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 20, 200, 20, hwnd, NULL, NULL, NULL);
    CreateWindow("STATIC", "Name:", WS_VISIBLE | WS_CHILD, 50, 50, 100, 20, hwnd, NULL, NULL, NULL);
    	hName = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 200, 20, hwnd, NULL, NULL, NULL);
    CreateWindow("STATIC", "Surname:", WS_VISIBLE | WS_CHILD, 50, 80, 100, 20, hwnd, NULL, NULL, NULL);
    	hSurname = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 80, 200, 20, hwnd, NULL, NULL, NULL);
    CreateWindow("STATIC", "Email:", WS_VISIBLE | WS_CHILD, 50, 110, 100, 20, hwnd, NULL, NULL, NULL);
    	hEmail = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 110, 200, 20, hwnd, NULL, NULL, NULL);
    CreateWindow("STATIC", "Phone:", WS_VISIBLE | WS_CHILD, 50, 140, 100, 20, hwnd, NULL, NULL, NULL);
    	hPhone = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 140, 200, 20, hwnd, NULL, NULL, NULL);
    CreateWindow("STATIC", "Password:", WS_VISIBLE | WS_CHILD, 50, 170, 100, 20, hwnd, NULL, NULL, NULL);
    	hPassword = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 200, 170, 200, 20, hwnd, NULL, NULL, NULL);
    CreateWindow("STATIC", "Confirm Password:", WS_VISIBLE | WS_CHILD, 50, 200, 140, 20, hwnd, NULL, NULL, NULL);
    	hConfirmPassword = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 200, 200, 200, 20, hwnd, NULL, NULL, NULL);
    CreateWindow("BUTTON", "Register", WS_VISIBLE | WS_CHILD, 180, 250, 200, 30, hwnd, (HMENU)2, NULL, NULL);
    
    currentPage = SIGNUP;
}

void SaveUser() {
    char userName[MAX_INPUT], name[MAX_INPUT], surName[MAX_INPUT], email[MAX_INPUT], phone[MAX_INPUT], password[MAX_INPUT], confirmPassword[MAX_INPUT];
    GetWindowText(hUsername, userName, MAX_INPUT);
    GetWindowText(hName, name, MAX_INPUT);
    GetWindowText(hSurname, surName, MAX_INPUT);
    GetWindowText(hEmail, email, MAX_INPUT);
    GetWindowText(hPhone, phone, MAX_INPUT);
    GetWindowText(hPassword, password, MAX_INPUT);
    GetWindowText(hConfirmPassword, confirmPassword, MAX_INPUT);
    
    
    if (strcmp(password, confirmPassword) != 0) {
        MessageBox(NULL, "Passwords do not match.", "Error", MB_OK);
        return;
    }
    
    FILE *f = fopen("userdata.txt", "a");
    if (f != NULL) {
        fprintf(f, "%s|%s|%s|%s|%s|%s\n", userName, name, surName, email, phone, password);
        fclose(f);
        MessageBox(NULL, "Signup successful! Please login.", "Success", MB_OK);
    } else {
        MessageBox(NULL, "Error saving user data.", "File Error", MB_OK);
    }
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
    
	    case WM_COMMAND: {
	        int wmId = LOWORD(wParam);
	
	        if (currentPage == WELCOME) {
	            if (wmId == 1) ShowSignup(hwnd);
	        } else if (currentPage == SIGNUP && wmId == 2) {
           	 	SaveUser();
        	} 
		}
	}
	
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
