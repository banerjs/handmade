/*
This is the first file that we are adding as part of this project
*/

#include <windows.h>

LRESULT CALLBACK MainWindowCallback(HWND Window,
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
            OutputDebugStringA("WM_SIZE\n");
        } break;

        // The window is about to be destroyed
        case WM_DESTROY:
        {
            OutputDebugStringA("WM_DESTROY\n");
        } break;

        // The user has clicked on the Red 'X' in the corner
        case WM_CLOSE:
        {
            OutputDebugStringA("WM_CLOSE\n");
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
            PatBlt(DeviceContext, X, Y, Width, Height, WHITENESS);

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


int CALLBACK WinMain(HINSTANCE Instance,
                     HINSTANCE PrevInstance,
                     LPSTR CommandLine,
                     int ShowCode)
{
    WNDCLASS WindowClass = {};                   // Initialize everything to 0

    // Then selectively initialize the members that we care about
    WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallback;
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
            for (;;)
            {
                BOOL MessageResult = GetMessage(&Message, 0, 0, 0); // Grab all
                if (MessageResult > 0)
                {
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
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
