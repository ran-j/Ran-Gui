
#pragma once

#include <memory>
#include <Render/Graphics.h>
#include <ControlManager.h>

namespace RanGui
{
    class UI
    {
    public:
        UI(void **hwnd);
        UI(ID3D11DeviceContext* deviceContext, IDXGISwapChain* swapChain);
        ~UI();

    public:
        void Initialize();
        void Update(float deltaTime);
        void Render();

    public:
        void ProcessWinProc(const MSG &msg);
        void OnResize(float width, float height);

    public:
        void SetClearColor(float r, float g, float b, float a);
        void SetClearColorOnRender(const bool &value);

    public:
        ControlManager *GetControlManager() const;

    private:
        std::unique_ptr<Graphics> m_graphics;
        std::unique_ptr<ControlManager> m_controlManager;
        float m_clearColor[4] = {0.1f, 0.1f, 0.1f, 1.0f};
        bool m_clearColorOnRender = true;
    };
}
