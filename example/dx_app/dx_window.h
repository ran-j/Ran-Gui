#pragma once
#include <Windows.h>
#include "Renderer.h"
#include <UI.h>

using namespace RanGui;
class DXWindow
{
public:
    DXWindow(HINSTANCE hInstance, int nCmdShow);
    ~DXWindow();

    HRESULT Initialize();
    void RunMessageLoop();

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HINSTANCE hInstance;
    HWND hwnd;
    Renderer renderer;
    UI *ui;
};
