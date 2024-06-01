#include <Controls/TextBox.h>
#include <Render/Graphics.h>

namespace RanGui
{
    TextBox::TextBox(float pos_x, float pos_y, float width, float height)
        : Control(pos_x, pos_y, width, height), m_focused(false),
          m_textColor(ControlColor::Black),
          m_backgroundColor(ControlColor::White),
          m_borderColor(ControlColor::Black)
    {
    }

    void TextBox::Initialize(Graphics &graphics)
    {
        if (!graphics.IsValid())
            return;

        Renderable::Initialize(graphics);

        auto renderTarget = graphics.GetRenderTarget();
        auto writeFactory = graphics.GetWriteFactory();

        renderTarget->CreateSolidColorBrush(m_textColor, &m_pTextBrush);
        renderTarget->CreateSolidColorBrush(m_backgroundColor, &m_pBackgroundBrush);
        renderTarget->CreateSolidColorBrush(m_borderColor, &m_pBorderBrush);
        renderTarget->CreateSolidColorBrush(ControlColor::Black, &m_pCursorBrush);

        writeFactory->CreateTextFormat(
            m_font.c_str(), nullptr, DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
            m_height - (m_height / 2), L"en-us", &m_pTextFormat);

        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    void TextBox::Render(Graphics &graphics)
    {
        if (!m_isVisible)
            return;

        DrawBackground(graphics);
        DrawBorder(graphics);
        DrawText(graphics);

        if (m_focused)
        {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastBlinkTime).count();

            if (elapsed > 500)
            {
                m_isCursorVisible = !m_isCursorVisible;
                m_lastBlinkTime = now;
            }

            if (m_isCursorVisible)
            {
                Microsoft::WRL::ComPtr<RAN_GUI_TEXT_LAYOUT> pTextLayout;

                auto writeFactory = graphics.GetWriteFactory();
                writeFactory->CreateTextLayout(
                    m_text.c_str(),
                    static_cast<UINT32>(m_text.length()),
                    m_pTextFormat.Get(),
                    m_width,
                    m_height,
                    &pTextLayout);

                DWRITE_TEXT_METRICS textMetrics;
                pTextLayout->GetMetrics(&textMetrics);

                float cursorHeight = m_height / 1.5f;
                float cursorTop = m_y + (m_height - cursorHeight) / 2.0f;
                RAN_GUI_RECT cursorRect = RAN_GUI_RECT(m_x + textMetrics.width + 6, cursorTop, m_x + textMetrics.width + 4, cursorTop + cursorHeight);
                graphics.FillRectangle(cursorRect, m_pTextBrush.Get());
            }
        }
    }

    void TextBox::DrawText(Graphics &graphics)
    {
        auto renderTarget = graphics.GetRenderTarget();
        renderTarget->DrawTextW(m_text.c_str(), (UINT32)m_text.length(),
                                m_pTextFormat.Get(),
                                RAN_GUI_RECT(m_x + 5.f, m_y, m_x + m_width - 5.f, m_y + m_height),
                                m_pTextBrush.Get());
    }

    void TextBox::DrawBackground(Graphics &graphics)
    {
        graphics.FillRectangle(RAN_GUI_RECT(m_x, m_y, m_x + m_width, m_y + m_height), m_pBackgroundBrush.Get());
    }

    void TextBox::DrawBorder(Graphics &graphics)
    {
        graphics.DrawRectangleRect(RAN_GUI_RECT(m_x, m_y, m_x + m_width, m_y + m_height), m_pBorderBrush.Get(), m_focused ? 2.0f : 1.0f);
    }

    void TextBox::SetText(const std::wstring &text)
    {
        m_text = text;
    }

    std::wstring TextBox::GetText() const
    {
        return m_text;
    }

    void TextBox::SetTextColor(const RAN_GUI_COLOR_F &color)
    {
        m_textColor = color;
        Initialize(*m_graphics);
    }

    void TextBox::SetFontFamilyName(const std::wstring &font)
    {
        m_font = font;
        Initialize(*m_graphics);
    }

    void TextBox::SetBackgroundColor(const RAN_GUI_COLOR_F &color)
    {
        m_backgroundColor = color;
        Initialize(*m_graphics);
    }

    void TextBox::SetBorderColor(const RAN_GUI_COLOR_F &color)
    {
        m_borderColor = color;
        Initialize(*m_graphics);
    }

    void TextBox::OnKeyDown(WPARAM key)
    {
        if (!m_focused)
            return;

        if (key == VK_BACK && !m_text.empty())
        {
            m_text.pop_back();
        }
    }

    void TextBox::OnChar(WPARAM ch)
    {
        if (!m_focused)
            return;

        if (ch >= 32 && ch <= 126)
        {
            m_text.push_back(static_cast<wchar_t>(ch));
        }
    }

    void TextBox::OnFocus(bool focused)
    {
        m_focused = focused;
    }
}