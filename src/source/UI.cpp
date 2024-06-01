
#include <UI.h>
#include <wrl.h>

namespace RanGui
{
#define GET_X_LPARAM(lp) ((float)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((float)(short)HIWORD(lp))
    // #define GET_WHEEL_DELTA_WPARAM(wParam) ((short)HIWORD(wParam))

    UI::UI(void **hwnd)
    {
        m_graphics = std::make_unique<Graphics>(hwnd);
        m_controlManager = std::make_unique<ControlManager>(m_graphics.get());
    }

    UI::UI(ID3D11DeviceContext* deviceContext, IDXGISwapChain* swapChain)
    {
        m_graphics = std::make_unique<Graphics>(deviceContext, swapChain);
		m_controlManager = std::make_unique<ControlManager>(m_graphics.get());
    }

    UI::~UI()
    {
        CoUninitialize();
    }

    void UI::Initialize()
    {
        CoInitialize(nullptr);
    }

    void UI::Update(float deltaTime)
    {
        UNREFERENCED_PARAMETER(deltaTime);
        // m_controlManager->Update(deltaTime);
    }

    void UI::Render()
    {
        m_graphics->BeginDraw();
        if (m_clearColorOnRender)
        {
            m_graphics->ClearScreen(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
        }
        m_controlManager->Render(*m_graphics);
        m_graphics->EndDraw();
    }

    ControlManager *UI::GetControlManager() const
    {
        return m_controlManager.get();
    }

    void UI::ProcessWinProc(const MSG &msg)
    {
        switch (msg.message)
        {
        case WM_MOUSEMOVE:
            m_controlManager->OnMouseMove(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam));
            break;
        case WM_LBUTTONDOWN:
            m_controlManager->OnMouseDown(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam));
            break;
        case WM_LBUTTONUP:
            m_controlManager->OnMouseUp(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam));
            break;
        case WM_KEYDOWN:
            m_controlManager->OnKeyDown(msg.wParam);
            break;
        case WM_CHAR:
            m_controlManager->OnChar(msg.wParam);
            break;
        case WM_MOUSEWHEEL:
            m_controlManager->OnMouseWheel((float)GET_WHEEL_DELTA_WPARAM(msg.wParam));
            break;
        }
    }

    void UI::OnResize(float width, float height)
    {
        m_graphics->Resize(width, height);
        // m_controlManager->OnResize(width, height);
    }

    void UI::SetClearColor(float r, float g, float b, float a)
    {
        m_clearColor[0] = r;
        m_clearColor[1] = g;
        m_clearColor[2] = b;
        m_clearColor[3] = a;
    }

    void UI::SetClearColorOnRender(const bool &value)
    {
        m_clearColorOnRender = value;
    }
}