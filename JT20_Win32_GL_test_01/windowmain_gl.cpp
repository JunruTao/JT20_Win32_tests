#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <gl/GL.h>

HDC dvcContext; //where to store pixel data
HGLRC rdrContext; //handle to OpenGL context

/*[Part1.1][Create a Handle to window]*/
HWND hWnd; //  <---- This is the *Handle* of the {_parent_window_}


LPCWSTR JT_MAIN_WIN_NAME = L"JT20 Test Window"; //  <---- Used in the *Creation* of {_parent_window_}
LPCWSTR parentCapTitle = L"JT-2020 First Window"; //  <---- Used in the *CAPTION*(Text on the window) of {_parent_window_}
LPCWSTR Error01 = L"Error 01: RegisterClassW issue tend to ";
LPCWSTR Error02 = L"Error 02: ParentWindowCreateW issue to tend to"; //  <---- *Error handling message* of {_parent_window_}



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


GLuint TextureCreation(INT16 index)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID); //this is 1st binding

	struct color 
    {
		unsigned char c[4]; //RGBA
	};

    color col[16 * 16] = {};

    for (int i = 0;i < 16 * 16;++i)
    {

		col[i].c[0] = rand() % 0xff;
		col[i].c[1] = rand() % 0xff;
		col[i].c[2] = rand() % 0xff;

    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 16, 16, 0, GL_RGBA, GL_UNSIGNED_BYTE, col);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
}


void RenderSquare()
{
    static GLuint plate = glGenLists(1);
    static bool first = true;
    static float nsize = 0.4f;

    if (first)  //build a list
    {
        first = false;

        GLuint htex = TextureCreation(1);
        glBindTexture(GL_TEXTURE_2D, htex);
        glNewList(plate, GL_COMPILE);
        glBegin(GL_QUADS);
        //front face
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-nsize, nsize, nsize);
            glTexCoord2f(0.0f, 0.5f);
            glVertex3f(nsize, nsize, nsize);
            glTexCoord2f(0.5f, 0.5f);
            glVertex3f(nsize, -nsize, nsize);
            glTexCoord2f(0.5f, 0.0f);
            glVertex3f(-nsize, -nsize, nsize);
        //back face
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(nsize, nsize, -nsize);
            glTexCoord2f(0.0f, 3.0f);
            glVertex3f(-nsize, nsize, -nsize);
            glTexCoord2f(3.0f, 3.0f);
            glVertex3f(-nsize, -nsize, -nsize);
            glTexCoord2f(3.0f, 0.0f);
            glVertex3f(nsize, -nsize, -nsize);
        //left face
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-nsize, nsize, -nsize);
            glTexCoord2f(0.0f, 0.1f);
            glVertex3f(-nsize, nsize, nsize);
            glTexCoord2f(0.1f, 0.1f);
            glVertex3f(-nsize, -nsize, nsize);
            glTexCoord2f(0.1f,0.0f);
            glVertex3f(-nsize, -nsize, -nsize);
        //right face
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(nsize, nsize, -nsize);
            glTexCoord2f(0.0f, 0.9f);
            glVertex3f(nsize, nsize, nsize);
            glTexCoord2f(0.9f, 0.9f);
            glVertex3f(nsize, -nsize, nsize);
            glTexCoord2f(0.9f, 0.0f);
            glVertex3f(nsize, -nsize, -nsize);
        //bot cap
            glTexCoord2f(0.1f, 0.1f);
            glVertex3f(-nsize, -nsize, nsize);
            glTexCoord2f(0.1f, 0.6f);
            glVertex3f(nsize, -nsize, nsize);
            glTexCoord2f(0.6f, 0.6f);
            glVertex3f(nsize, -nsize, -nsize);
            glTexCoord2f(0.6f, 0.1f);
            glVertex3f(-nsize, -nsize, -nsize);
        //top cap
            glTexCoord2f(0.2f, 0.2f);
            glVertex3f(-nsize, nsize, nsize);
            glTexCoord2f(0.2f, 0.3f);
            glVertex3f(nsize, nsize, nsize);
            glTexCoord2f(0.3f, 0.3f);
            glVertex3f(nsize, nsize, -nsize);
            glTexCoord2f(0.3f, 0.2f);
            glVertex3f(-nsize, nsize, -nsize);

        glEnd();
        glEndList();        // Done Building The box List
        glCallList(plate);
    }
    else
        glCallList(plate);
}



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

    /*NEW*/WNDCLASS winClass = {};
    /*NEW*/winClass.lpfnWndProc = WndProc;
    /*NEW*/winClass.hInstance = hInstance;
    /*NEW*/winClass.lpszClassName = JT_MAIN_WIN_NAME;


    /*[Register Class window]*/
    if (!RegisterClass(&winClass))
    {
        MessageBoxW(NULL, Error01, JT_MAIN_WIN_NAME, MB_ICONERROR);
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

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    bool running = true;
    /*[PART 2.3]----THE 'BIG WHILE LOOP'----*/
    while (running)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Translate the message and dispatch it to WindowProc()
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // If the message is WM_QUIT, exit the while loop
        if (msg.message == WM_QUIT || msg.message == WM_CLOSE) {
            running = false;
            DestroyWindow(hWnd);
        }

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderSquare();
        glRotatef(1.9f,  1.0f, 1.0f, 0.0f);
        glRotatef(-0.8f, 0.0f, 0.0f, 1.0f);
        SwapBuffers(dvcContext);
    }



    return 0;
}
/*------------------------------------------------- */



/*[WindowProc] - Window Procedure*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT userMessage, WPARAM wParam, LPARAM lParam)
{

    switch (userMessage)
    {
    case WM_CREATE:
    {

        //_______________________GL_______________________
        PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd  
                1,                     // version number  
                PFD_DRAW_TO_WINDOW |   // support window  
                PFD_SUPPORT_OPENGL |   // support OpenGL  
                PFD_DOUBLEBUFFER,      // double buffered  
                PFD_TYPE_RGBA,         // RGBA type  
                24,                    // 24-bit color depth  
                0, 0, 0, 0, 0, 0,      // color bits ignored  
                0,                     // no alpha buffer  
                0,                     // shift bit ignored  
                0,                     // no accumulation buffer  
                0, 0, 0, 0,            // accum bits ignored  
                32,                    // 32-bit z-buffer      
                0,                     // no stencil buffer  
                0,                     // no auxiliary buffer  
                PFD_MAIN_PLANE,        // main layer  
                0,                     // reserved  
                0, 0, 0                // layer masks ignored  
        };

        dvcContext = GetDC(hWnd);//get handle from HWND
        int pixelFormat = ChoosePixelFormat(dvcContext, &pfd);
        SetPixelFormat(dvcContext, pixelFormat, &pfd);
        rdrContext = wglCreateContext(dvcContext);
        wglMakeCurrent(dvcContext, rdrContext);
        glViewport(0, 0, 800, 600);
        return 0;


    }break;


    case WM_DESTROY:
    {
        //_____________________________new for [GL]
        glDisable(GL_TEXTURE_2D);
        ReleaseDC(hWnd, dvcContext);
        wglDeleteContext(rdrContext);
        PostQuitMessage(0);
        return 0;

    }break;

    }

    return DefWindowProc(hWnd, userMessage, wParam, lParam);
}


