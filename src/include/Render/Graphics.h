
#pragma once
#include <Controls/ControlColor.h>

#include <d3d11.h>
#include <d2d1_1.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wrl.h>
#include <memory>
#include <string>

#ifdef _MSC_VER
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "windowscodecs")
#endif

namespace RanGui
{

    struct RAN_GUI_POINT : public D2D1_POINT_2F
    {
        RAN_GUI_POINT() = default;
        RAN_GUI_POINT(D2D1_POINT_2F point) : D2D1_POINT_2F(point) {}
        RAN_GUI_POINT(float x, float y) : D2D1_POINT_2F(D2D1::Point2F(x, y)) {}
    };

    struct RAN_GUI_ELLIPSE : public D2D1_ELLIPSE
    {
        RAN_GUI_ELLIPSE() = default;
        RAN_GUI_ELLIPSE(D2D1_ELLIPSE ellipse) : D2D1_ELLIPSE(ellipse) {}
        RAN_GUI_ELLIPSE(float x, float y, float radiusX, float radiusY) : D2D1_ELLIPSE(D2D1::Ellipse(D2D1::Point2F(x, y), radiusX, radiusY)) {}
        RAN_GUI_ELLIPSE(D2D1_POINT_2F point, float radiusX, float radiusY) : D2D1_ELLIPSE(D2D1::Ellipse(point, radiusX, radiusY)) {}
    };

    struct RAN_GUI_RECT : public D2D1_RECT_F
    {
        RAN_GUI_RECT() = default;
        RAN_GUI_RECT(D2D1_RECT_F rect) : D2D1_RECT_F(rect) {}
        RAN_GUI_RECT(float left, float top, float right, float bottom) : D2D1_RECT_F(D2D1::RectF(left, top, right, bottom)) {}
    };

    struct RAN_GUI_ROUNDED_RECT : public D2D1_ROUNDED_RECT
    {
        RAN_GUI_ROUNDED_RECT() = default;
        RAN_GUI_ROUNDED_RECT(D2D1_ROUNDED_RECT rect) : D2D1_ROUNDED_RECT(rect) {}
        RAN_GUI_ROUNDED_RECT(float left, float top, float right, float bottom, float radiusX, float radiusY) : D2D1_ROUNDED_RECT(D2D1::RoundedRect(D2D1::RectF(left, top, right, bottom), radiusX, radiusY)) {}
        RAN_GUI_ROUNDED_RECT(RAN_GUI_RECT rect, float radiusX, float radiusY) : D2D1_ROUNDED_RECT(D2D1::RoundedRect(rect, radiusX, radiusY)) {}
    };

    typedef ID2D1SolidColorBrush RAN_GUI_SOLID_COLOR_BRUSH;
    typedef IDWriteTextFormat RAN_GUI_TEXT_FORMAT;
    typedef ID2D1LinearGradientBrush RAN_GUI_LINEAR_GRADIENT_BRUSH;
    typedef IDWriteTextLayout RAN_GUI_TEXT_LAYOUT;
    typedef ID2D1PathGeometry RAN_GUI_PATH_GEOMETRY;

    class Graphics
    {
    public:
        Graphics(void **hwnd);
        Graphics(ID3D11DeviceContext *deviceContext, IDXGISwapChain *swapChain);

        ~Graphics();

        void BeginDraw();
        void EndDraw();
        void ClearScreen(float r, float g, float b, float a = 1.0f);

        void DrawRectangle(float x, float y, float width, float height, ID2D1Brush *brush, float strokeWidth = 1.0f);
        void DrawRectangleRect(RAN_GUI_RECT rect, ID2D1Brush *brush, float strokeWidth = 1.0f);
        void DrawText(const wchar_t *text, float x, float y, float width, float height, ID2D1Brush *brush, RAN_GUI_TEXT_FORMAT *textFormat);
        void FillRoundedRectangle(D2D1_ROUNDED_RECT rect, ID2D1Brush *brush);
        void DrawRoundedRectangle(D2D1_ROUNDED_RECT rect, ID2D1Brush *brush, float strokeWidth = 1.0f);
        void FillRectangle(RAN_GUI_RECT rect, ID2D1Brush *brush);
        void DrawLine(RAN_GUI_POINT p1, RAN_GUI_POINT p2, ID2D1Brush *brush, float strokeWidth = 1.0f);
        void FillEllipse(RAN_GUI_ELLIPSE ellipse, ID2D1Brush *brush);
        void DrawEllipse(RAN_GUI_ELLIPSE ellipse, ID2D1Brush *brush, float strokeWidth = 1.0f);

        ID2D1RenderTarget *GetRenderTarget() const;
        ID2D1Factory *GetFactory() const;
        IDWriteFactory *GetWriteFactory() const;

        bool IsValid() const { return this != nullptr; }

        void Resize(float width, float height);

    private:
        Microsoft::WRL::ComPtr<ID2D1Factory> m_pFactory;
        Microsoft::WRL::ComPtr<ID2D1Factory1> m_pDXFactory;
        
        Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;
        Microsoft::WRL::ComPtr<ID2D1RenderTarget> m_pDxRenderTarget;

        Microsoft::WRL::ComPtr<IDWriteFactory> m_pDWriteFactory;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDeviceContext;
        Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain;

        bool m_bIsUsingSwapChain = false;
    };
}