/*
This is the first file that we are adding as part of this project
*/

#include <windows.h>

#define internal static
#define local_persist static
#define global_variable static

// WTF?!?! Global variable....
global_variable bool Running;

// This gets called everytime the window is resized
internal void Win32ResizeDIBSection(int Width, int Height)
{
    CreateDIBSection();
}


// Repainting of things within the window happens in three different cases
// 1. Windows thinks pixels are stale
// 2. User actions will cause pixels to be stale
// 3. Game render needs to be forced at 30fps
internal void Win32UpdateWindow(HWND Window, int X, int Y, int Width, int Height)
{
    StretchDIBits();
}


// This is the callback that Windows expects in order to handle events on the
// created window
LRESULT CALLBACK Win32MainWindowCallback(HWND Window,
                                         UINT Message,
                                         WPARAM WParam,
                                         LPARAM LParam)
{
    LRESULT Result = 0;

    switch(Message)
    {
        // The Size of the window has changed
        case WM_SIZE:
        {
            RECT ClientRect;
            GetClientRect(Window, &ClientRect);
            int Width = ClientRect.right - ClientRect.left;
            int Height = ClientRect.bottom - ClientRect.top;
            Win32ResizeDIBSection(Width, Height);
            OutputDebugStringA("WM_SIZE\n");
        } break;

        // The window is about to be destroyed
        case WM_DESTROY:
        {
            // TODO: Remove dependence on global vars
            Running = false;
        } break;

        // The user has clicked on the Red 'X' in the corner
        case WM_CLOSE:
        {
            // TODO: Remove dependence on global vars
            Running = false;
        } break;

        // We are the currently active window
        case WM_ACTIVATEAPP:
        {
            OutputDebugStringA("WM_ACTIVATEAPP\n");
        } break;

        // Draw something in the window
        case WM_PAINT:
        {
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(Window, &Paint);

            int X = Paint.rcPaint.left;
            int Y = Paint.rcPaint.top;
            int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
            int Width = Paint.rcPaint.right - Paint.rcPaint.left;
            Win32UpdateWindow(Window, X, Y, Width, Height);

            EndPaint(Window, &Paint);
        } break;

        // All other messages
        default:
        {
            // OutputDebugStringA("Default\n");
            Result = DefWindowProc(Window, Message, WParam, LParam);
        } break;
    }

    return Result;
}


// Main method. Expected by Windows
int CALLBACK WinMain(HINSTANCE Instance,
                     HINSTANCE PrevInstance,
                     LPSTR CommandLine,
                     int ShowCode)
{
    WNDCLASS WindowClass = {};                   // Initialize everything to 0

    // Then selectively initialize the members that we care about
    WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    WindowClass.lpfnWndProc = Win32MainWindowCallback;
    WindowClass.hInstance = Instance;
    // WindowClass.hIcon; // Save this for later
    WindowClass.lpszClassName = "HandmadeHeroWindowClass";

    if (RegisterClass(&WindowClass))    // Register the WindowClass
    {
        // If successful, create a window
        HWND WindowHandle = CreateWindowEx(0,
                                           WindowClass.lpszClassName,
                                           "Handmade Hero",
                                           WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                           CW_USEDEFAULT,
                                           CW_USEDEFAULT,
                                           CW_USEDEFAULT,
                                           CW_USEDEFAULT,
                                           0,
                                           0,
                                           Instance,
                                           0);
        if (WindowHandle)
        {
            // If successful, setup message passing
            MSG Message;
            Running = true;
            while(Running)
            {
                BOOL MessageResult = GetMessageA(&Message, 0, 0, 0); // Grab all
                if (MessageResult > 0)
                {
                    TranslateMessage(&Message);
                    DispatchMessageA(&Message);
                }
                else
                {
                    break;          // Error, or quit received. Exit
                }
            }
        }
        else
        {
            // TODO: Logging
        }
    }
    else
    {
        // TODO: Logging needs to be added
    }

    return 0;
}
