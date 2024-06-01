#pragma once
#include <Controls/ControlToolTippable.h>
#include <Controls/Label.h>
#include <Controls/ControlColor.h>
#include <memory>
#include <string>

namespace RanGui
{
    enum class ButtonStyle
    {
        Round,
        None,
        Flat
    };

    class Button : public ControlToolTippable
    {
    public:
        Button(const std::wstring &text, float pos_x, float pos_y, float width, float height, ButtonStyle style = ButtonStyle::Round);
        Button(const std::wstring &text, float pos_x, float pos_y, ButtonStyle style = ButtonStyle::Round);
        Button(const std::wstring &text, ButtonStyle style = ButtonStyle::Round);

    public:
        virtual void Render(Graphics &graphics) override;
        virtual void Initialize(Graphics &graphics) override;
        virtual void OnMouseDown(float x, float y) override;
        virtual void OnMouseMove(float x, float y) override;

    public:
        virtual void SetPosition(float x, float y) override;

    public:
        void SetStyle(ButtonStyle style);
        void SetColor(const RAN_GUI_COLOR_F &startColor, const RAN_GUI_COLOR_F &endColor);
        void SetBorderColor(const RAN_GUI_COLOR_F &color);
        void SetHoverColor(const RAN_GUI_COLOR_F &color);
        void SetShadowColor(const RAN_GUI_COLOR_F &color);

    public:
        void SetText(const std::wstring &text);
        void SetFontFamilyName(const std::wstring &font);
        void SetTextColor(const RAN_GUI_COLOR_F &color);
        void SetTextAlignment(TextAlignment alignment);

    private:
        RAN_GUI_COLOR_F m_startColor = ControlColor::White;
        RAN_GUI_COLOR_F m_endColor = ControlColor::LightGray;

        RAN_GUI_COLOR_F m_hoverColor = ControlColor::White;
        RAN_GUI_COLOR_F m_borderColor = ControlColor::Black;

        RAN_GUI_COLOR_F m_shadowColor = ControlColor::Gray;

        ButtonStyle m_style;

        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBorderBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pHoverBorderBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pShadowBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_LINEAR_GRADIENT_BRUSH> m_pGradientBrush;

        std::unique_ptr<Label> m_label;

        bool m_isHovered = false;
    };
}