//Readme: This project is licensed under the terms of the MIT license.
//Author: Parcode


#include "Window.h"

//Window* window = nullptr;

Window::Window()
{
}

LRESULT CALLBACK WndProc(
    HWND hwnd, UINT msg,
    WPARAM wparam, LPARAM lparam
) {
    switch (msg) {

    case WM_CREATE: {
    
        //fired when window is created
        Window* window =
            (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
       
        SetWindowLongPtr(
            hwnd, GWL_USERDATA, (LONG_PTR)window
        );

        window->setHWND(hwnd);
        window->onCreate();

        break;
    }

    case WM_DESTROY: {
        
        //fired when window is destroyed
        Window* window =
            (Window*)GetWindowLong(hwnd,GWL_USERDATA);
        window->onDestroy();
        ::PostQuitMessage(0);
        break;
    }

    default: return ::DefWindowProc(
        hwnd, msg, 
        wparam, lparam
    );

    }

    return NULL;
} 

bool Window::init()
{
    WNDCLASSEX wc;
    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = NULL;
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.style = NULL;
    wc.lpfnWndProc = &WndProc;


    // if the registration of class fails it returns false
    if (!::RegisterClassEx(&wc)) return false;

    //if (!window) window = this;
    
    //creates a window
    m_hwnd = ::CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass",
        L"DirectX Application",WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,CW_USEDEFAULT,
        1024,768,
        NULL,NULL,NULL,this
    );
    
    //returns false if creation fails
    if (!m_hwnd) return false;

    //show window
    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);

    // set this flag to indicate that the window is running
    m_is_run = true;

    return true;
}

bool Window::broadcast()
{
    MSG msg;

    while (::PeekMessage(&msg,NULL,0,0,PM_REMOVE) > 0) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
    }

    //window->onUpdate();
    this->onUpdate();



    Sleep(0);

    return true;
}

bool Window::release()
{
    //destroy the window
    if (!::DestroyWindow(m_hwnd)) return false;

    return true;
}

bool Window::isRun()
{
    return m_is_run;
}

RECT Window::getClientWindowRect()
{
    RECT rc;
    ::GetClientRect(this->m_hwnd, &rc);
    return rc;
}

void Window::setHWND(HWND hwnd)
{
    this->m_hwnd = hwnd;
}

void Window::onDestroy()
{
    m_is_run = false;
}

Window::~Window()
{
}













