#include <Render/Graphics.h>
#include <stdexcept>

namespace RanGui
{
    Graphics::Graphics(void **hwnd)
    {
        HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m_pFactory.GetAddressOf());
        if (FAILED(hr))
        {
            throw std::runtime_error("Failed to create Direct2D factory");
        }

        hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown **>(m_pDWriteFactory.GetAddressOf()));
        if (FAILED(hr))
        {
            throw std::runtime_error("Failed to create DirectWrite factory");
        }

        RECT rc;
        GetClientRect((HWND)hwnd, &rc);

        hr = m_pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties((HWND)hwnd, D2D1::SizeU(rc.right, rc.bottom)),
            &m_pRenderTarget);

        if (FAILED(hr))
        {
            throw std::runtime_error("Failed to create HWND render target");
        }

        m_bIsUsingSwapChain = false;
    }

    Graphics::Graphics(ID3D11DeviceContext *deviceContext, IDXGISwapChain *swapChain) : m_pDeviceContext(deviceContext), m_pSwapChain(swapChain)
    {
        HRESULT hr = S_OK;

        D2D1_FACTORY_OPTIONS options = {};
#if defined(_DEBUG)
        options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options, m_pDXFactory.GetAddressOf());
        if (FAILED(hr))
        {
            throw std::runtime_error("Failed to create Direct2D factory");
        }

        hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown **>(m_pDWriteFactory.GetAddressOf()));
        if (FAILED(hr))
        {
            throw std::runtime_error("Failed to create DirectWrite factory");
        }

        Microsoft::WRL::ComPtr<IDXGISurface> dxgiSurface;
        hr = m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiSurface));
        if (FAILED(hr))
        {
            throw std::runtime_error("Failed to get DXGI back buffer");
        }

        FLOAT dpiX = static_cast<FLOAT>(GetDpiForWindow(GetDesktopWindow()));
        FLOAT dpiY = dpiX;

        D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
            dpiX,
            dpiY);

        hr = m_pDXFactory->CreateDxgiSurfaceRenderTarget(
            dxgiSurface.Get(),
            &props,
            m_pDxRenderTarget.GetAddressOf());

        if (FAILED(hr))
        {
            throw std::runtime_error("Failed to create DXGI surface render target");
        }

        m_bIsUsingSwapChain = true;
    }

    Graphics::~Graphics()
    {
        m_pFactory.Reset();
        m_pDXFactory.Reset();
        m_pRenderTarget.Reset();
        m_pDWriteFactory.Reset();
        m_pDxRenderTarget.Reset();
    }

    void Graphics::BeginDraw()
    {
        GetRenderTarget()->BeginDraw();
    }

    void Graphics::EndDraw()
    {
        HRESULT hr = GetRenderTarget()->EndDraw();
        if (FAILED(hr))
        {
            throw std::runtime_error("Failed to end draw");
        }
    }

    void Graphics::ClearScreen(float r, float g, float b, float a)
    {
        GetRenderTarget()->Clear(D2D1::ColorF(r, g, b, a));
    }

    void Graphics::DrawRectangle(float x, float y, float width, float height, ID2D1Brush *brush, float strokeWidth)
    {
        GetRenderTarget()->DrawRectangle(RAN_GUI_RECT(x, y, width, height), brush, strokeWidth);
    }

    void Graphics::DrawRectangleRect(RAN_GUI_RECT rect, ID2D1Brush *brush, float strokeWidth)
    {
        GetRenderTarget()->DrawRectangle(rect, brush, strokeWidth);
    }

    void Graphics::DrawText(const wchar_t *text, float x, float y, float width, float height, ID2D1Brush *brush, RAN_GUI_TEXT_FORMAT *textFormat)
    {
        GetRenderTarget()->DrawText(text, (UINT32)wcslen(text), textFormat, RAN_GUI_RECT(x, y, width, height), brush);
    }

    void Graphics::FillRoundedRectangle(D2D1_ROUNDED_RECT rect, ID2D1Brush *brush)
    {
        GetRenderTarget()->FillRoundedRectangle(&rect, brush);
    }

    void Graphics::DrawRoundedRectangle(D2D1_ROUNDED_RECT rect, ID2D1Brush *brush, float strokeWidth)
    {
        GetRenderTarget()->DrawRoundedRectangle(rect, brush, strokeWidth);
    }

    void Graphics::FillRectangle(RAN_GUI_RECT rect, ID2D1Brush *brush)
    {
        GetRenderTarget()->FillRectangle(rect, brush);
    }

    void Graphics::DrawLine(RAN_GUI_POINT p1, RAN_GUI_POINT p2, ID2D1Brush *brush, float strokeWidth)
    {
        GetRenderTarget()->DrawLine(p1, p2, brush, strokeWidth);
    }

    void Graphics::FillEllipse(RAN_GUI_ELLIPSE ellipse, ID2D1Brush *brush)
    {
        GetRenderTarget()->FillEllipse((D2D1_ELLIPSE)ellipse, brush);
    }

    void Graphics::DrawEllipse(RAN_GUI_ELLIPSE ellipse, ID2D1Brush *brush, float strokeWidth)
    {
        GetRenderTarget()->DrawEllipse((D2D1_ELLIPSE)ellipse, brush, strokeWidth);
    }

    ID2D1RenderTarget *Graphics::GetRenderTarget() const
    {
        if (m_bIsUsingSwapChain)
        {
            return m_pDxRenderTarget.Get();
        }
        else
        {
            return m_pRenderTarget.Get();
        }
    }

    ID2D1Factory *Graphics::GetFactory() const
    {
        if (m_bIsUsingSwapChain)
        {
            return m_pDXFactory.Get();
        }
        else
        {
            return m_pFactory.Get();
        }
    }

    IDWriteFactory *Graphics::GetWriteFactory() const
    {
        return m_pDWriteFactory.Get();
    }

    void Graphics::Resize(float width, float height)
    {
        if (m_bIsUsingSwapChain)
        {
            m_pDxRenderTarget.Reset();

            Microsoft::WRL::ComPtr<IDXGISurface> dxgiSurface;
            HRESULT hr = m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiSurface));
            if (FAILED(hr))
            {
                throw std::runtime_error("Failed to get DXGI back buffer");
            }

            D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
                D2D1_RENDER_TARGET_TYPE_DEFAULT,
                D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
                0,
                0);

            hr = m_pDXFactory->CreateDxgiSurfaceRenderTarget(
                dxgiSurface.Get(),
                &props,
                m_pDxRenderTarget.GetAddressOf());

            if (FAILED(hr))
            {
                throw std::runtime_error("Failed to create DXGI surface render target");
            }
        }
        else
        {
            HRESULT hr = m_pRenderTarget->Resize(D2D1::SizeU((UINT32)width, (UINT32)height));
            if (FAILED(hr))
            {
                throw std::runtime_error("Failed to resize HWND render target");
            }
        }
    }
}