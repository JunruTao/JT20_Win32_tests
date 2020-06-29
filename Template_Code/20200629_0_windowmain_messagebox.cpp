#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <CommCtrl.h>

/*[Create a Handle to window]*/
HWND hWnd;

/*[Message Field]*/
/*
//Using Unicode string type: [LPCWSTR]
//An [LPCWSTR] is a 32-bit pointer to a constant string of 16-bit Unicode characters;
//Translate: "Long Pointer to Constant Wide String"
*/
LPCWSTR szTestName = L"Test Window"; // L"A" is for the unicode "Long" recognition
LPCWSTR parentCapTitle = L"Startup Code"; // Start-up Code
LPCWSTR Error01 = L"Error 01: RegisterClassW issue tend to ";
LPCWSTR Error02 = L"Error 02: ParentWindowCreateW issue to tend to";

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



/*[Windows Main function]*/
int WINAPI WinMain(
    HINSTANCE hInstance, 
    HINSTANCE hPrevInstance, 
    PSTR szCmdLine, 
    int iCmdShow) 
{
   //[Template Here] -> MessageBoxW(HWND, LPCWSTR, LPCWSTR, UNIT);
    MessageBoxW(NULL, L"Window is working", L"Window", 0);

    return 0;
}




/*[WindowProc] - Window Procedure*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT userMessage, WPARAM wParam, LPARAM lParam) 
{
    return 0;
    
}