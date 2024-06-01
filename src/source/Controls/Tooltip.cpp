#include <Controls/Tooltip.h>
#include <Render/Graphics.h>

namespace RanGui
{
    Tooltip::Tooltip(float pos_x, float pos_y, float width, float height)
        : Panel(pos_x, pos_y, width, height),
          m_textColor(ControlColor::Black)
    {
        SetBackgroundColor(ControlColor::Yellow);
    }

    void Tooltip::SetText(const std::wstring &text)
    {
        m_text = text;
    }

    void Tooltip::SetTextColor(const RAN_GUI_COLOR_F &color)
    {
        m_textColor = color;
    }

    void Tooltip::SetFontFamilyName(const std::wstring &font)
    {
        m_font = font;
        Initialize(*m_graphics);
    }

    void Tooltip::Initialize(Graphics &graphics)
    {
        Panel::Initialize(graphics);

        if (!graphics.IsValid())
            return;
        
        auto renderTarget = graphics.GetRenderTarget();
        auto dwriteFactory = graphics.GetWriteFactory();
 
        renderTarget->CreateSolidColorBrush(m_textColor, &m_pTextBrush);

        dwriteFactory->CreateTextFormat(
            m_font.c_str(),
            NULL,
            DWRITE_FONT_WEIGHT_REGULAR,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            12.0f,
            L"en-us",
            &m_pTextFormat);

        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    void Tooltip::Render(Graphics &graphics)
    {
        Panel::Render(graphics);

        if (!m_isVisible)
            return;

        auto renderTarget = graphics.GetRenderTarget();
        renderTarget->DrawTextW(
            m_text.c_str(),
            static_cast<UINT32>(m_text.length()),
            m_pTextFormat.Get(),
            D2D1::RectF(m_x + 5, m_y, m_x + m_width - 5, m_y + m_height),
            m_pTextBrush.Get());
    }
}