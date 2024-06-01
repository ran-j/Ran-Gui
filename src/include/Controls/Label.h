#pragma once
#include <Controls/Control.h>
#include <string>

namespace RanGui
{
    enum class TextAlignment
    {
        Center,
        Left,
        Right
    };

    class Label : public Control
    {
    public:
        Label(const std::wstring &text, float pos_x, float pos_y, float width, float height, float textSize = 12.0f);
        Label(const std::wstring &text, float pos_x, float pos_y);
        Label(const std::wstring &text);

    public:
        virtual void Render(Graphics &graphics) override;
        virtual void Initialize(Graphics &graphics) override;

    public:
        void SetText(const std::wstring &text);
        float GetTextSize() const;
        void SetFontSize(float textSize);
        float GetFontSize() const;
        void SetAlignment(TextAlignment alignment);

    public:
        void SetFontFamilyName(const std::wstring &font);
        void SetColor(const RAN_GUI_COLOR_F &color);

    private:
        RAN_GUI_COLOR_F m_color;
        std::wstring m_font;
        TextAlignment m_alignment;

        std::wstring m_text;
        float m_textSize;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_TEXT_FORMAT> m_pTextFormat;
    };
}