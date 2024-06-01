#include <Controls/CheckBox.h>
#include <Render/Graphics.h>

namespace RanGui
{
    CheckBox::CheckBox(const std::wstring &text, float pos_x, float pos_y, float width, float height)
        : ControlToolTippable(pos_x, pos_y, width, height), m_text(text), m_isChecked(false),
          m_backgroundColor(ControlColor::White),
          m_borderColor(ControlColor::Black),
          m_checkColor(ControlColor::Black),
          m_textColor(ControlColor::Black),
          m_textPosition(CheckBoxTextPosition::Left)
    {
    }

    void CheckBox::Initialize(Graphics &graphics)
    {
        if (!graphics.IsValid())
            return;

        ControlToolTippable::Initialize(graphics);

        auto renderTarget = graphics.GetRenderTarget();

        renderTarget->CreateSolidColorBrush(m_backgroundColor, &m_pBackgroundBrush);
        renderTarget->CreateSolidColorBrush(m_borderColor, &m_pBorderBrush);
        renderTarget->CreateSolidColorBrush(m_checkColor, &m_pCheckBrush);
        renderTarget->CreateSolidColorBrush(m_textColor, &m_pTextBrush);

        auto dwriteFactory = graphics.GetWriteFactory();

        dwriteFactory->CreateTextFormat(
            m_text_font.c_str(),
            NULL,
            DWRITE_FONT_WEIGHT_REGULAR,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            m_textSize,
            L"en-us",
            &m_pTextFormat);

        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

        CreateTextLayout(graphics);
    }

    void CheckBox::Render(Graphics &graphics)
    {
        ControlToolTippable::Render(graphics);

        if (!m_isVisible)
            return;

        graphics.FillRectangle(RAN_GUI_RECT(m_x, m_y, m_x + m_height, m_y + m_height), m_pBackgroundBrush.Get());
        graphics.DrawRectangleRect(RAN_GUI_RECT(m_x, m_y, m_x + m_height, m_y + m_height), m_pBorderBrush.Get(), 1.0f);

        if (m_isChecked)
        {
            graphics.DrawLine(RAN_GUI_POINT(m_x + 3, m_y + m_height / 2), RAN_GUI_POINT(m_x + m_height / 2, m_y + m_height - 3), m_pCheckBrush.Get(), 2.0f);
            graphics.DrawLine(RAN_GUI_POINT(m_x + m_height / 2, m_y + m_height - 3), RAN_GUI_POINT(m_x + m_height - 3, m_y + 3), m_pCheckBrush.Get(), 2.0f);
        }

        DrawText(graphics);
    }

    void CheckBox::SetText(const std::wstring &text)
    {
        m_text = text;
        CreateTextLayout(*m_graphics);
    }

    void CheckBox::SetChecked(bool checked)
    {
        m_isChecked = checked;
    }

    bool CheckBox::IsChecked() const
    {
        return m_isChecked;
    }

    void CheckBox::SetTextColor(const RAN_GUI_COLOR_F &color)
    {
        m_textColor = color;
        Initialize(*m_graphics);
    }

    void CheckBox::SetFontSize(float textSize)
    {
        m_textSize = textSize;
        Initialize(*m_graphics);
    }

    void CheckBox::SetFontFamilyName(const std::wstring &font)
    {
        m_text_font = font;
        Initialize(*m_graphics);
    }

    void CheckBox::SetBackgroundColor(const RAN_GUI_COLOR_F &color)
    {
        m_backgroundColor = color;
        Initialize(*m_graphics);
    }

    void CheckBox::SetBorderColor(const RAN_GUI_COLOR_F &color)
    {
        m_borderColor = color;
        Initialize(*m_graphics);
    }

    void CheckBox::SetCheckColor(const RAN_GUI_COLOR_F &color)
    {
        m_checkColor = color;
        Initialize(*m_graphics);
    }

    void CheckBox::OnMouseDown(float x, float y)
    {
        if (Intersect(x, y))
        {
            m_isChecked = !m_isChecked;
        }
    }

    void CheckBox::SetTextPosition(CheckBoxTextPosition position)
    {
        m_textPosition = position;
    }

    void CheckBox::DrawText(Graphics &graphics)
    {
        auto renderTarget = graphics.GetRenderTarget();

        if (m_textLayout == nullptr)
        {
            CreateTextLayout(graphics);
        }

        DWRITE_TEXT_METRICS textMetrics;
        m_textLayout->GetMetrics(&textMetrics);

        RAN_GUI_RECT layoutRect;

        if (m_textPosition == CheckBoxTextPosition::Left)
        {
            layoutRect = RAN_GUI_RECT(m_x - textMetrics.width - 6, m_y, m_x - 6, m_y + m_height);
        }
        else if (m_textPosition == CheckBoxTextPosition::Above)
        {
            layoutRect = RAN_GUI_RECT(m_x, m_y - m_height - 5, m_x + m_width, m_y);
        }
        else if (m_textPosition == CheckBoxTextPosition::Right)
        {
            layoutRect = RAN_GUI_RECT(m_x + m_height + 5, m_y, m_x + m_height + 5 + textMetrics.width, m_y + m_height);
        }

        renderTarget->DrawTextW(
            m_text.c_str(),
            static_cast<UINT32>(m_text.length()),
            m_pTextFormat.Get(),
            layoutRect,
            m_pTextBrush.Get());
    }

    void CheckBox::CreateTextLayout(Graphics &graphics)
    {
        if (!graphics.IsValid())
            return;
            
        if (m_textLayout != nullptr)
        {
            m_textLayout.Reset();
        }
        auto dwriteFactory = graphics.GetWriteFactory();

        dwriteFactory->CreateTextLayout(
            m_text.c_str(),
            static_cast<UINT32>(m_text.length()),
            m_pTextFormat.Get(),
            FLT_MAX,
            FLT_MAX,
            &m_textLayout);
    }
}