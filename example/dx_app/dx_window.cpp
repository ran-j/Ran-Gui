#include "dx_window.h"
#include <Controls/Button.h>

DXWindow::DXWindow(HINSTANCE hInstance, int nCmdShow)
    : hInstance(hInstance), hwnd(NULL), ui(nullptr)
{
}

DXWindow::~DXWindow()
{
    delete ui;
}

HRESULT DXWindow::Initialize()
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"DirectXExample";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_APPLICATION);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create the window
    RECT rc = {0, 0, 800, 600};
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    hwnd = CreateWindow(L"DirectXExample", L"DirectX Example", WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, this);
    if (!hwnd)
        return E_FAIL;

    ShowWindow(hwnd, SW_SHOW);

    // Initialize DirectX renderer
    HRESULT hr = renderer.Initialize(hwnd);
    if (FAILED(hr))
        return hr;

    // Initialize UI
    ui = new UI(renderer.GetDeviceContext(), renderer.GetSwapChain());
    ui->SetClearColorOnRender(false);
    ui->SetClearColor(0.0f, 0.2f, 0.4f, 1.0f);
    ui->Initialize();

    auto button = std::make_unique<Button>(L"Click Me", 150.f, 200.f, 200.f, 50.f);
    button->AddEventListener(std::make_shared<LambdaEventListener>([](const Event &event)
                                                                   {
        if (event.GetType() == EventType::Click)
        {
            MessageBox(NULL, L"Button clicked!", L"Notification", MB_OK);
        } }));
    ui->GetControlManager()->AddControl(std::move(button));

    return S_OK;
}

void DXWindow::RunMessageLoop()
{
    MSG msg = {0};
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            renderer.Render([&]()
                            {
                if (ui)
            {ui->Render();} });
        }
    }
}

LRESULT CALLBACK DXWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DXWindow *window = nullptr;
    if (uMsg == WM_NCCREATE)
    {
        window = static_cast<DXWindow *>(reinterpret_cast<CREATESTRUCT *>(lParam)->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
    }
    else
    {
        window = reinterpret_cast<DXWindow *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (window)
    {
        switch (uMsg)
        {
        case WM_SIZE:
            if (window->ui)
            {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                window->ui->OnResize(width, height);
                InvalidateRect(hwnd, NULL, TRUE);
            }
            return 0;
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MOUSEMOVE:
            if (window->ui)
            {
                window->ui->ProcessWinProc({hwnd, uMsg, wParam, lParam});
                InvalidateRect(hwnd, NULL, TRUE);
            }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
