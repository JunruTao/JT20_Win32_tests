#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <CommCtrl.h>

/*[Create a Handle to window]*/
HWND hWnd; //  <---- This is the *Handle* of the {_parent_window_}


/*[Message Field]*/
/*
    Using Unicode string type: [LPCWSTR]
    An [LPCWSTR] is a 32-bit pointer to a constant string of 16-bit Unicode characters;
    [LPCWSTR] Translate: "Long Pointer to Constant Wide String"
    [L"Text"] is for the unicode "Long" recognition
*/
LPCWSTR szTestName = L"Test Window"; //  <---- Used in the *Creation* of {_parent_window_}
LPCWSTR parentCapTitle = L"Create Window"; //  <---- Used in the *CAPTION* of {_parent_window_}
LPCWSTR Error01 = L"Error 01: RegisterClassW issue tend to ";
LPCWSTR Error02 = L"Error 02: ParentWindowCreateW issue to tend to"; //  <---- *Error handling message* of {_parent_window_}

/*[WindowProc] - Window Procedure*/
/*
In Win32 application programming, WindowProc (or window procedure)
is a user-defined callback function that processes messages sent to a window.
This function is specified when an application registers its window class.
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
/*[Type Walk-Through]*/
/*
    [1]---LRESUL:    -> (Long Pointer to RESULT) Signed result of message processing.
    [2]---CALLBACK:  -> <Function Type> define functions with the __stdcall calling convention.
    [3]---UINT:      -> (Unsigned Int)
    [4]---WPARAM:    -> (Word Parameter) Message Parameter, a <UINT_PTR> type.
    [5]---LPARAM:    -> (Long Parameter) Message Parameter, a <UINT_PTR> type.

    [Interface of Window Procedure] -
    {
        [>>input] - HWND hWnd     -->[A handle to window];
        [>>input] - UNIT userMsg  -->[The message];
        [>>input] - WPARAM wParam -->[Additional Message info];
        [>>input] - LPARAM lParam -->[Additional Message info];
    }
*/



/*--------------[Windows Main function]--------------*/
int WINAPI WinMain(
    HINSTANCE hInstance, 
    HINSTANCE hPrevInstance, 
    PSTR szCmdLine, 
    int iCmdShow) 
{
  
    /*[PART 2.1]----CREATE WINDOW CLASS STRUCTURE----*/
    MSG msg = { 0 }; // Messsage

    /*[IMPORTANT]Defining the `structure member` for WND-CLASS-[W]*/
    /*------------------------------------------------
      |  [News]:This structure has been superseded  |
      |  by the WNDCLASSEX structure used with the  |
      |  RegisterClassEx function.                  |
      ------------------------------------------------
    */
    WNDCLASSW wsw = { 0 };
    /*(1)WSW*/wsw.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    /*(2)WSW*/wsw.lpszClassName = szTestName;
    /*(3)WSW*/wsw.lpfnWndProc = WndProc;
    /*(4)WSW*/wsw.hInstance = hInstance;
    /*(5)WSW*/wsw.hIcon = LoadIconW(NULL, IDI_APPLICATION);
    /*(6)WSW*/wsw.hCursor = LoadCursorW(NULL, IDC_ARROW);
    /*(7)WSW*/wsw.hbrBackground = (HBRUSH)(COLOR_WINDOW);

    /*[Register Class window]*/
    if (!RegisterClassW(&wsw)) 
    {
        MessageBoxW(NULL,Error01,szTestName,MB_ICONERROR);
    }



    /*[PART 2.2]----CREATING NEW WINDOW----*/
    hWnd = CreateWindowW(
        szTestName,
        parentCapTitle,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, /* Window Start Position x */
        100, /* Window Start Position y */
        400, /* Height of the window*/
        400, /* Width of the Window*/
        NULL, /*Handle of window already done*/
        NULL, /*--hMenu*/
        NULL, /*--hInstance*/
        NULL /*--lpParam*/
    );

    if (hWnd == NULL) 
    {
        MessageBoxW(NULL, Error02, szTestName, 0); //The [0] here uType Default for Okay push button
        return 0;
    }

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    /*[PART 2.3]----THE 'BIG WHILE LOOP'----*/
    while (GetMessageW(&msg, NULL, 0, 0)) 
    {

        TranslateMessage(&msg);
        DispatchMessageW(&msg);


    }

    return 0;
}
/*------------------------------------------------- */



/*[WindowProc] - Window Procedure*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT userMessage, WPARAM wParam, LPARAM lParam) 
{
    switch (userMessage)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hWnd, userMessage, wParam, lParam);
}