#include <Controls/PictureBox.h>
#include <Render/Graphics.h>

namespace RanGui
{
    PictureBox::PictureBox(const std::wstring &imagePath, float pos_x, float pos_y, float width, float height)
        : Control(pos_x, pos_y, width, height), m_imagePath(imagePath)
    {
    }

    PictureBox::~PictureBox()
    {
    }

    void PictureBox::Initialize(Graphics &graphics)
    {
        if (!graphics.IsValid())
            return;

        Renderable::Initialize(graphics);

        if (!m_pWICFactory)
        {
            CoCreateInstance(
                CLSID_WICImagingFactory,
                nullptr,
                CLSCTX_INPROC_SERVER,
                IID_PPV_ARGS(&m_pWICFactory));
        }

        LoadImage(m_imagePath);
    }

    void PictureBox::LoadImage(const std::wstring &imagePath)
    {
        Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
        m_pWICFactory->CreateDecoderFromFilename(
            imagePath.c_str(),
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &decoder);

        Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
        decoder->GetFrame(0, &frame);

        Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
        m_pWICFactory->CreateFormatConverter(&converter);

        converter->Initialize(
            frame.Get(),
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            0.f,
            WICBitmapPaletteTypeCustom);

        auto renderTarget = m_graphics->GetRenderTarget();
        renderTarget->CreateBitmapFromWicBitmap(
            converter.Get(),
            nullptr,
            &m_pBitmap);
    }

    void PictureBox::Render(Graphics &graphics)
    {
        if (!m_isVisible)
            return;

        auto renderTarget = graphics.GetRenderTarget();
        renderTarget->DrawBitmap(
            m_pBitmap.Get(),
            RAN_GUI_RECT(m_x, m_y, m_x + m_width, m_y + m_height));
    }

    void PictureBox::SetImage(const std::wstring &imagePath)
    {
        m_imagePath = imagePath;
        LoadImage(imagePath);
    }
}