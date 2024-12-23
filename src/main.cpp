#include "../include/Window.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Window mainWindow(hInstance);

    //Create window and run message loop
    mainWindow.createWindow(L"date ciara sim", 500, 500, 200, 200);
    mainWindow.changeIcon("../assets/Icon.ico");
    mainWindow.refreshWindow();
    mainWindow.runMessageLoop();
    return 0;   
}