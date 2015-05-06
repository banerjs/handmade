/*
This is the first file that we are adding as part of this project
*/

#include <windows.h>

int CALLBACK WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow)
{
    MessageBox(0, "This is Handmade", "Handmade", MB_OK|MB_ICONINFORMATION);

    return 0;
}
