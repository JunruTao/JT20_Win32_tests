#define _CRT_SECURE_NO_WARNINGS
#define U_MENU_ITEM_TEST_1 1
#define U_MENU_ITEM_TEST_2 2
#define U_MENU_ITEM_TEST_3 3

#include <windows.h>
#include <ShObjIdl.h>
#include <atlbase.h> // Contains the declaration of CComPtr.

/*[Part1.1][Create a Handle to window]*/
HWND hWnd; //  <---- This is the *Handle* of the {_parent_window_}

/*NEW [Part 3.1]*/
HMENU hMenu; //  <---- This is the *Handle* of the {_Menu_}
HMENU hMenu2;


/*[Part1.2][Message Field]*/
/*
    Using Unicode string type: [LPCWSTR]
    An [LPCWSTR] is a 32-bit pointer to a constant string of 16-bit Unicode characters;
    [LPCWSTR] Translate: "Long Pointer to Constant Wide String"
    [L"Text"] is for the unicode "Long" recognition
*/
LPCWSTR JT_MAIN_WIN_NAME = L"JT20 Test Window"; //  <---- Used in the *Creation* of {_parent_window_}
LPCWSTR parentCapTitle = L"JT-2020 First Window"; //  <---- Used in the *CAPTION*(Text on the window) of {_parent_window_}
LPCWSTR Error01 = L"Error 01: RegisterClassW issue tend to ";
LPCWSTR Error02 = L"Error 02: ParentWindowCreateW issue to tend to"; //  <---- *Error handling message* of {_parent_window_}

/*[Part1.3-a][WindowProc] - Window Procedure*/
/*
In Win32 application programming, WindowProc (or window procedure)
is a user-defined callback function that processes messages sent to a window.
This function is specified when an application registers its window class.

LRESULT is an integer value that your program returns to Windows. It contains 
your program's response to a particular message. The meaning of this value 
depends on the message code. CALLBACK is the calling convention for the function.
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
/*[Part1.3-b][Type Walk-Through]*/
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
/*[Part1.4]---WinMain Inputs*/
int WINAPI WinMain(
    HINSTANCE hInstance, 
    HINSTANCE hPrevInstance, 
    PSTR szCmdLine, 
    int iCmdShow) 
{
  
    /*[PART 2.1]----CREATE WINDOW CLASS STRUCTURE----*/
    MSG msg = {}; // Messsage

    /*[Part1.5][IMPORTANT]Defining the `structure member` for WND-CLASS*/
    /*NEW - Updates According to Win32 website -- Using WNDCLASS*/
    /*-------------------------------------------------------------------------
    A window class defines a set of behaviors that several windows might have 
    in common. For example, in a group of buttons, each button has a similar 
    behavior when the user clicks the button. Of course, buttons are not comp-
    letely identical; each button displays its own text string and has its own
    screen coordinates. Data that is unique for each window is called instance 
    data.
    -------------------------------------------------------------------------*/
    /*NEW*/WNDCLASS winClass = {};
    /*NEW*/winClass.lpfnWndProc = WndProc;
    /*NEW*/winClass.hInstance = hInstance;
    /*NEW*/winClass.lpszClassName = JT_MAIN_WIN_NAME;


    /*[Register Class window]*/
    if (!RegisterClass(&winClass)) 
    {
        MessageBoxW(NULL,Error01,JT_MAIN_WIN_NAME,MB_ICONERROR);
    }



    /*[PART 2.2]----CREATING NEW WINDOW----*/
    /*NEW - Updates According to Win32 website -- Using CreateWindowEx*/
    hWnd = CreateWindowEx(
        0,                          //Optional Window style 
        JT_MAIN_WIN_NAME,           //Window Class name
        parentCapTitle,             //Window Caption text
        WS_OVERLAPPEDWINDOW,        //Window Style(WS_EX_OVER...) - will show no closing buttons
        CW_USEDEFAULT,              //Window Pos.Start X,
        CW_USEDEFAULT,              //Window Pos.Start Y,
        800,              //Window Width,
        600,              //Window Height
        NULL,             //Parent Window
        NULL,            //Menu
        hInstance,        //Instance handle
        NULL              //Additional application data
    );

    if (hWnd == NULL) 
    {
        MessageBoxW(NULL, Error02, JT_MAIN_WIN_NAME, 0); //The [0] here uType Default for Okay push button
        return 0;
    }

    ShowWindow(hWnd, iCmdShow);
    //UpdateWindow(hWnd);

    /*[PART 2.3]----THE 'BIG WHILE LOOP'----*/
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        /*
        The TranslateMessage function is related to keyboard input. 
        It translates keystrokes (key down, key up) into characters. 
        You do not really have to know how this function works; just
        remember to call it before DispatchMessage.
        */
        TranslateMessage(&msg);
        /*
        The DispatchMessage function tells the operating system to 
        call the window procedure of the window that is the target 
        of the message. In other words, the operating system looks 
        up the window handle in its table of windows, finds the fu-
        nction pointer associated with the window, and invokes the 
        function.
        */
        DispatchMessage(&msg);

    }

    return 0;
}
/*------------------------------------------------- */



/*[WindowProc] - Window Procedure*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT userMessage, WPARAM wParam, LPARAM lParam) 
{
    /*[Part 4.2]Define handle*/
    hMenu = CreateMenu();

    switch (userMessage)
    {


    /*[Part 4.3 -start]-------------Menu Creations in here---------------*/
    case WM_CREATE:
    {
        hMenu = CreateMenu();
        hMenu2 = CreateMenu();

        AppendMenuW
        (
            hMenu2,
            MF_STRING,
            U_MENU_ITEM_TEST_2, // ^^^^Define the identifier constant (At top)
            L"&Open"
        );

        AppendMenuW
        (
            hMenu2,
            MF_STRING,
            U_MENU_ITEM_TEST_3, // ^^^^Define the identifier constant (At top)
            L"&OpenPrac"
        );

        AppendMenuW
        (
            hMenu2,
            MF_STRING,
            U_MENU_ITEM_TEST_1, // ^^^^Define the identifier constant (At top)
            L"&About"
        );

        AppendMenuW
        (
            hMenu,
            MF_POPUP,
            (UINT_PTR)hMenu2, L"&File"
        );
    
        SetMenu(hWnd, hMenu);
    }

    case WM_COMMAND:
        //Add another swith for wParam commands
        switch (wParam) 
        {
                //***[add]Using a MessageBeep ("Clinnggg"Sound when you clik) to add the logic to make it beep...
            case U_MENU_ITEM_TEST_1:
                MessageBeep(MB_ICONINFORMATION);
                break;


                //***[add] Practice COM, useShObjIdl.h to open file explorer Dialog and loadfile.
                //***
            case U_MENU_ITEM_TEST_2:
            {
                HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
                    COINIT_DISABLE_OLE1DDE);
                if (SUCCEEDED(hr))
                {
                    IFileOpenDialog* pFileOpen;

                    // Create the FileOpenDialog object.

                    /*---Inside '(..)' is [vtable](virtual method table)
                    V-Table is a table of function pointers. 
                    The vtable is how COM binds a method call 
                    to its implementation at run time.
                    */
                    hr = CoCreateInstance(
                        CLSID_FileOpenDialog,
                        NULL,
                        CLSCTX_ALL,
                        /*Using [__uuidof]- Retrieves the GUID attached to the expression.
                            ---[GUID/UUID]- 'Globally Unique Identifier' 
                            (or 'Universally Unique Identifier'). 
                            It is a 128-bit integer number used to identify resources. 

                        The compiler extracts the GUID value from the header, 
                        so no library export is necessary.*/

                        __uuidof(pFileOpen),//IID_IFileOpenDialog, 
                        reinterpret_cast<void**>(&pFileOpen) // or these 2 lines with: `IID_PPV_ARGS(&pFileOpen)`
                    );

                    if (SUCCEEDED(hr))
                    {
                        // Show the Open dialog box.
                        hr = pFileOpen->Show(NULL);//[Open ]reference counting(COM)

                        // Get the file name from the dialog box.
                        if (SUCCEEDED(hr))
                        {
                            IShellItem* pItem;
                            hr = pFileOpen->GetResult(&pItem);
                            if (SUCCEEDED(hr))
                            {
                                PWSTR pszFilePath;
                                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                                // Display the file name to the user.
                                if (SUCCEEDED(hr))
                                {
                                    MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
                                    CoTaskMemFree(pszFilePath);
                                }
                                pItem->Release();
                            }
                        }
                        pFileOpen->Release();//[Relese ]similar to heap management's malloc->free
                        /*here -> checkout the __Safe-Release__Template: 
                        URL: https://docs.microsoft.com/en-us/windows/win32/learnwin32/com-coding-practices
                        and other info. Basically check if the **ptp COM object is there? and released?
                        Then release the pointer and shift handle to NULL;
                        */
                    }
                    CoUninitialize();
                }
            }break;

            case U_MENU_ITEM_TEST_3:
            {
                //Using the COM smart pointers: CComPtr<T> type, similar to std::unique_ptr<T> in C++
                //CComPtr is contained in the header <atlbase.h>
                //Cross referencing in menu item 2 and see the difference~ Usage is same with C++ smart ptrs
                HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
                    COINIT_DISABLE_OLE1DDE);
                if (SUCCEEDED(hr))
                {
                    CComPtr<IFileOpenDialog> pFileOpen;

                    // Create the FileOpenDialog object.
                    //Compare with the one up: CoCreateInstance line, much cleaner;
                    hr = pFileOpen.CoCreateInstance(__uuidof(FileOpenDialog));
                    if (SUCCEEDED(hr))
                    {
                        // Show the Open dialog box.
                        hr = pFileOpen->Show(NULL);

                        // Get the file name from the dialog box.
                        if (SUCCEEDED(hr))
                        {
                            CComPtr<IShellItem> pItem;
                            hr = pFileOpen->GetResult(&pItem);
                            if (SUCCEEDED(hr))
                            {
                                PWSTR pszFilePath;
                                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                                // Display the file name to the user.
                                if (SUCCEEDED(hr))
                                {
                                    MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
                                    CoTaskMemFree(pszFilePath);
                                }
                            }

                            // pItem goes out of scope.
                        }

                        // pFileOpen goes out of scope.
                    }
                    CoUninitialize();
                }

            }break;
        }
        break;

    case WM_PAINT:
        {
        PAINTSTRUCT pntStruc;
        HDC hdc = BeginPaint(hWnd, &pntStruc); //hDC-[handle to device context] 

        //...All Painting occurs here...

        FillRect(hdc, &pntStruc.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(hWnd, &pntStruc);
        }
        return 0;

    /*[NEW]Working with a WM_CLOSE asking if closing*/
    case WM_CLOSE:
        if (MessageBox(hWnd, L"Quiting the Program?", parentCapTitle, MB_OKCANCEL) == IDOK) 
        {
            DestroyWindow(hWnd);
        }
        return 0;
    //Exiting the program
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, userMessage, wParam, lParam);
}