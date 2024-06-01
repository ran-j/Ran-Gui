#pragma once
#include <Controls/Control.h>
#include <wincodec.h>
#include <string>

namespace RanGui
{
    class PictureBox : public Control
    {
    public:
        PictureBox(const std::wstring &imagePath, float pos_x, float pos_y, float width, float height);
        ~PictureBox();

        virtual void Render(Graphics &graphics) override;
        virtual void Initialize(Graphics &graphics) override;

        void SetImage(const std::wstring &imagePath);

    private:
        void LoadImage(const std::wstring &imagePath);

        std::wstring m_imagePath;
        Microsoft::WRL::ComPtr<ID2D1Bitmap> m_pBitmap;
        Microsoft::WRL::ComPtr<IWICImagingFactory> m_pWICFactory;
    };
}