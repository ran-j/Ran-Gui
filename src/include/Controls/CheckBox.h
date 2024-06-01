#pragma once
#include <Controls/ControlToolTippable.h>
#include <Controls/Label.h>
#include <Controls/ControlColor.h>
#include <string>

namespace RanGui
{
    enum class CheckBoxTextPosition
    {
        Left,
        Above,
        Right
    };

    class CheckBox : public ControlToolTippable
    {
    public:
        CheckBox(const std::wstring &text, float pos_x, float pos_y, float width, float height);

    public:
        virtual void Render(Graphics &graphics) override;
        virtual void Initialize(Graphics &graphics) override;

    public:
        void SetText(const std::wstring &text);
        void SetChecked(bool checked);
        bool IsChecked() const;

    public:
        void SetTextColor(const RAN_GUI_COLOR_F &color);
        void SetBackgroundColor(const RAN_GUI_COLOR_F &color);
        void SetBorderColor(const RAN_GUI_COLOR_F &color);
        void SetCheckColor(const RAN_GUI_COLOR_F &color);
        void SetFontSize(float textSize);
        void SetFontFamilyName(const std::wstring &font);

    public:
        void SetTextPosition(CheckBoxTextPosition position);

    public:
        void OnMouseDown(float x, float y) override;

    private:
        std::wstring m_text;
        std::wstring m_text_font = L"Arial";
        float m_textSize = 12.0f;

        bool m_isChecked;

        CheckBoxTextPosition m_textPosition;

        RAN_GUI_COLOR_F m_backgroundColor;
        RAN_GUI_COLOR_F m_borderColor;
        RAN_GUI_COLOR_F m_checkColor;
        RAN_GUI_COLOR_F m_textColor;

        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBackgroundBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBorderBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pCheckBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pTextBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_TEXT_LAYOUT> m_textLayout;

        Microsoft::WRL::ComPtr<RAN_GUI_TEXT_FORMAT> m_pTextFormat;

        void DrawText(Graphics &graphics);
        void CreateTextLayout(Graphics &graphics);
    };
}