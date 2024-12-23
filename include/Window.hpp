#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <windows.h>

class Window {
public:
    Window(HINSTANCE hInstance); // Constructor

    int createWindow(WCHAR TITLE[], int sizeX, int sizeY, int posX, int posY); // Window creation
    int refreshWindow();
    int changeIcon(char filePath[]);
    void runMessageLoop(); // Run the message loop

private:
    HINSTANCE hInstance;
    HWND hwnd;
    static const wchar_t CLASS_NAME[];
    WNDCLASSEXW WINDOW; // Window class object for registration

    // WindowProc: Static method to handle messages
    static LRESULT CALLBACK WindowProcExW(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // WINDOW_HPP
