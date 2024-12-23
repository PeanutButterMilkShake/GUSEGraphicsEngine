#include "../../include/Window.hpp"

const wchar_t Window::CLASS_NAME[] = L"WindowClass";

// Constructor to initialize the window class
Window::Window(HINSTANCE hInstance) {
    this->hInstance = hInstance;

    // Initialize the WNDCLASSEXW
    WINDOW = {};  // Initialize to zero
    WINDOW.cbSize = sizeof(WNDCLASSEXW);  // Set the size of the WNDCLASSEXW structure
    WINDOW.lpfnWndProc = WindowProcExW;      // Set the window procedure function
    WINDOW.hInstance = hInstance;         // Set the instance handle
    WINDOW.lpszClassName = CLASS_NAME;    // Set the class name
    WINDOW.style = CS_HREDRAW | CS_VREDRAW;  // Set window style for resizing behavior

    // Optional settings
    WINDOW.hIcon = LoadIcon(NULL, IDI_APPLICATION);  // Default application icon
    WINDOW.hCursor = LoadCursor(NULL, IDC_ARROW);   // Default arrow cursor
    WINDOW.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // White background
    WINDOW.lpszMenuName = NULL;  // No menu associated
    WINDOW.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // Small application icon

    // Register the window class
    RegisterClassExW(&WINDOW);
}

// Public method to create and show the window
int Window::createWindow(WCHAR title[], int sizeX, int sizeY, int posX, int posY) {
    // Create the window
    hwnd = CreateWindowExW(
        0,                          // Optional window styles
        CLASS_NAME,                 // Window class name
        title,      // Window title
        WS_OVERLAPPEDWINDOW,        // Standard window style with minimize, maximize, and close buttons
        posX, posY, sizeX, sizeY,   // Position and size of the window
        NULL, NULL, hInstance, NULL // Parent window, menu, instance handle, additional parameters
    );
    ShowWindow(hwnd, SW_SHOW);
    return 0;
}

int Window::changeIcon(char filePath[])
{
    HICON newIcon = (HICON)LoadImage(hInstance, filePath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)newIcon);
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)newIcon);

    return 0;
}

int Window::refreshWindow()
{
    //Update the window
    UpdateWindow(hwnd);
    return 0;
}

// Run the message loop to process window events
void Window::runMessageLoop() {
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);  // Translate virtual-key codes
        DispatchMessage(&msg);   // Dispatch the message to the window procedure
    }
}

// Window procedure to handle messages
LRESULT CALLBACK Window::WindowProcExW(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);  // Post the message to quit the message loop
            return 0;
        default:
            return DefWindowProcW(hwnd, uMsg, wParam, lParam); // Default message handling
    }
}