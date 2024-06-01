
#include <Controls/Button.h>
#include <Render/Graphics.h>

namespace RanGui
{
    Button::Button(const std::wstring &text, float pos_x, float pos_y, float width, float height, ButtonStyle style)
        : ControlToolTippable(pos_x, pos_y, width, height), m_style(style)
    {
        m_label = std::make_unique<Label>(text, pos_x, pos_y, width, height);
    }

    Button::Button(const std::wstring &text, float pos_x, float pos_y, ButtonStyle style) : ControlToolTippable(pos_x, pos_y, 50.f, 20.f), m_style(style)
    {
        m_label = std::make_unique<Label>(text, pos_x, pos_y);
    }

    Button::Button(const std::wstring &text, ButtonStyle style) : ControlToolTippable(0.f, 0.f, 50.f, 20.f), m_style(style)
    {
        m_label = std::make_unique<Label>(text, 0.f, 0.f);
    }

    void Button::Initialize(Graphics &graphics)
    {
        if (!graphics.IsValid())
            return;

        ControlToolTippable::Initialize(graphics);

        auto renderTarget = graphics.GetRenderTarget();
        ID2D1GradientStopCollection *pGradientStops = nullptr;
        D2D1_GRADIENT_STOP gradientStops[2];
        gradientStops[0] = D2D1::GradientStop(0.0f, m_startColor);
        gradientStops[1] = D2D1::GradientStop(1.0f, m_endColor);
        renderTarget->CreateGradientStopCollection(gradientStops, 2, &pGradientStops);

        renderTarget->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(
                RAN_GUI_POINT(m_x, m_y),
                RAN_GUI_POINT(m_x + m_width, m_y + m_height)),
            pGradientStops,
            &m_pGradientBrush);

        renderTarget->CreateSolidColorBrush(m_borderColor, &m_pBorderBrush);
        renderTarget->CreateSolidColorBrush(m_hoverColor, &m_pHoverBorderBrush);
        renderTarget->CreateSolidColorBrush(m_shadowColor, &m_pShadowBrush);

        m_label->SetPosition(m_x, m_y);
        m_label->SetSize(m_width, m_height);
        m_label->Initialize(graphics);

        pGradientStops->Release();
    }

    void Button::SetColor(const RAN_GUI_COLOR_F &startColor, const RAN_GUI_COLOR_F &endColor)
    {
        m_startColor = startColor;
        m_endColor = endColor;
        Initialize(*m_graphics);
    }

    void Button::SetStyle(ButtonStyle style)

    {
        m_style = style;
    }

    void Button::SetBorderColor(const RAN_GUI_COLOR_F &color)
    {
        m_borderColor = color;
        Initialize(*m_graphics);
    }

    void Button::SetHoverColor(const RAN_GUI_COLOR_F &color)
    {
        m_hoverColor = color;
        Initialize(*m_graphics);
    }

    void Button::SetShadowColor(const RAN_GUI_COLOR_F &color)
    {
        m_shadowColor = color;
        Initialize(*m_graphics);
    }

    void Button::SetText(const std::wstring &text)
    {
        m_label->SetText(text);
    }

    void Button::SetFontFamilyName(const std::wstring &font)
    {
        m_label->SetFontFamilyName(font);
    }

    void Button::SetTextColor(const RAN_GUI_COLOR_F &color)
    {
        m_label->SetColor(color);
    }

    void Button::SetTextAlignment(TextAlignment alignment)
    {
        m_label->SetAlignment(alignment);
    }

    void Button::SetPosition(float x, float y)
    {
        ControlToolTippable::SetPosition(x, y);
        m_label->SetPosition(x, y);
    }

    void Button::Render(Graphics &graphics)
    {
        ControlToolTippable::Render(graphics);

        if (!m_isVisible)
            return;

        if (m_style == ButtonStyle::Round)
        {
            auto shadowRoundedRect = RAN_GUI_ROUNDED_RECT(RAN_GUI_RECT(m_x + 3, m_y + 3, m_x + m_width + 3, m_y + m_height + 3), 10.0f, 10.0f);
            graphics.FillRoundedRectangle(shadowRoundedRect, m_pShadowBrush.Get());

            auto roundedButtonRect = RAN_GUI_ROUNDED_RECT(RAN_GUI_RECT(m_x, m_y, m_x + m_width, m_y + m_height), 10.0f, 10.0f);
            graphics.FillRoundedRectangle(roundedButtonRect, m_pGradientBrush.Get());
            graphics.DrawRoundedRectangle(roundedButtonRect, m_isHovered ? m_pHoverBorderBrush.Get() : m_pBorderBrush.Get(), 2.0f);
        }
        else if (m_style == ButtonStyle::Flat)
        {
            auto shadowFlatRect = RAN_GUI_RECT(m_x + 3, m_y + 3, m_x + m_width + 3, m_y + m_height + 3);
            graphics.FillRectangle(shadowFlatRect, m_pShadowBrush.Get());

            auto flatButtonRect = RAN_GUI_RECT(m_x, m_y, m_x + m_width, m_y + m_height);
            graphics.FillRectangle(flatButtonRect, m_pGradientBrush.Get());
            graphics.DrawRectangleRect(flatButtonRect, m_isHovered ? m_pHoverBorderBrush.Get() : m_pBorderBrush.Get(), 2.0f);
        }
        else if (m_style == ButtonStyle::None)
        {
            // Do not draw the button shape, only render the label
        }

        m_label->Render(graphics);
    }

    void Button::OnMouseMove(float x, float y)
    {
        Control::OnMouseMove(x, y);
        if (Intersect(x, y))
        {
            m_isHovered = true;
        }
        else
        {
            m_isHovered = false;
        }
    }

    void Button::OnMouseDown(float x, float y)
    {
        if (Intersect(x, y))
        {
        }
    }
}