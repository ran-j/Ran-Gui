#include "dx_window.h"

int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int nCmdShow = SW_SHOW;

    DXWindow window(hInstance, nCmdShow);
    if (FAILED(window.Initialize()))
    {
        return 0;
    }

    window.RunMessageLoop();
    return 0;
}
