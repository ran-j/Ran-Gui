#include <Controls/Label.h>
#include <Render/Graphics.h>

namespace RanGui
{
    Label::Label(const std::wstring &text, float pos_x, float pos_y, float width, float height, float textSize)
        : Control(pos_x, pos_y, width, height), m_text(text), m_textSize(textSize), m_color(ControlColor::Black), m_alignment(TextAlignment::Center), m_font(L"Arial")
    {
    }

    Label::Label(const std::wstring &text, float pos_x, float pos_y) : Label(text, pos_x, pos_y, 30.f, 30.f, 12.0f)
    {
        m_width = static_cast<float>(m_text.length() * 10);
    }

    Label::Label(const std::wstring &text) : Label(text, 0.f, 0.f, 30.f, 30.f, 12.0f)
    {
        m_width = static_cast<float>(m_text.length() * 10);
    }

    void Label::Initialize(Graphics &graphics)
    {
        if (!graphics.IsValid())
            return;

        Renderable::Initialize(graphics);

        auto renderTarget = graphics.GetRenderTarget();
        auto writeFactory = graphics.GetWriteFactory();

        renderTarget->CreateSolidColorBrush(m_color, &m_pBrush);
        writeFactory->CreateTextFormat(
            m_font.c_str(),
            nullptr,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            m_textSize,
            L"en-US",
            &m_pTextFormat);

        switch (m_alignment)
        {
        case TextAlignment::Left:
            m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
            break;
        case TextAlignment::Center:
            m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
            break;
        case TextAlignment::Right:
            m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
            break;
        }

        m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    void Label::SetText(const std::wstring &text)
    {
        m_text = text;
    }

    float Label::GetTextSize() const
    {
        return static_cast<float>(m_text.length());
    }

    void Label::SetFontSize(float textSize)
    {
        m_textSize = textSize;
        Initialize(*m_graphics);
    }

    float Label::GetFontSize() const
    {
        return m_textSize;
    }

    void Label::SetAlignment(TextAlignment alignment)
    {
        m_alignment = alignment;
        Initialize(*m_graphics);
    }

    void Label::SetFontFamilyName(const std::wstring &font)
    {
        m_font = font;
        Initialize(*m_graphics);
    }

    void Label::SetColor(const RAN_GUI_COLOR_F &color)
    {
        m_color = color;
        Initialize(*m_graphics);
    }

    void Label::Render(Graphics &graphics)
    {
        if (!m_isVisible)
            return;

        graphics.DrawText(m_text.c_str(), m_x, m_y, m_x + m_width, m_y + m_height, m_pBrush.Get(), m_pTextFormat.Get());
    }
}