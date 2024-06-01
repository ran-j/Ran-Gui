#pragma once
#include <Controls/Panel.h>
#include <string>

namespace RanGui
{
    class Tooltip : public Panel
    {
    public:
        Tooltip(float pos_x, float pos_y, float width, float height);

    public:
        void SetText(const std::wstring &text);
        void SetTextColor(const RAN_GUI_COLOR_F &color);

    public:
        void SetFontFamilyName(const std::wstring &font);

    public:
        virtual void Render(Graphics &graphics);
        virtual void Initialize(Graphics &graphics);

    private:
        std::wstring m_text;
        std::wstring m_font;

        RAN_GUI_COLOR_F m_backgroundColor;
        RAN_GUI_COLOR_F m_textColor;
 
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pTextBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_TEXT_FORMAT> m_pTextFormat;
    };
}