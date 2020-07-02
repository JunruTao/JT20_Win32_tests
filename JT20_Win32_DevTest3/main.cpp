#include <Windows.h>
#include "base_window_CORE.h"
//#include "win_main.h"
#include "win_paint_circle.h"



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    CircleWindow win;
    //MainWindow win;

    if (!win.Create(L"Drawing a Circle - D2D1", WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }

    ShowWindow(win.Window(), nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
