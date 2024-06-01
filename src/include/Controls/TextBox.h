#pragma once
#include <Controls/Control.h>
#include <string>
#include <chrono>

namespace RanGui
{
    class TextBox : public Control
    {
    public:
        TextBox(float pos_x, float pos_y, float width, float height);

    public:
        virtual void Render(Graphics &graphics) override;
        virtual void Initialize(Graphics &graphics) override;

    public:
        void SetText(const std::wstring &text);
        std::wstring GetText() const;

    public:
        void SetTextColor(const RAN_GUI_COLOR_F &color);
        void SetFontFamilyName(const std::wstring &font);

    public:
        void SetBackgroundColor(const RAN_GUI_COLOR_F &color);
        void SetBorderColor(const RAN_GUI_COLOR_F &color);

    public:
        void OnKeyDown(WPARAM key);
        void OnChar(WPARAM ch);
        void OnFocus(bool focused);

    private:
        std::wstring m_text;
        std::wstring m_font = L"Arial";

        bool m_focused;
        bool m_isCursorVisible;

        std::chrono::time_point<std::chrono::steady_clock> m_lastBlinkTime;

        RAN_GUI_COLOR_F m_textColor;
        RAN_GUI_COLOR_F m_backgroundColor;
        RAN_GUI_COLOR_F m_borderColor;

        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pTextBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBackgroundBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBorderBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pCursorBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_TEXT_FORMAT> m_pTextFormat;

        void DrawText(Graphics &graphics);
        void DrawBackground(Graphics &graphics);
        void DrawBorder(Graphics &graphics);
    };
}