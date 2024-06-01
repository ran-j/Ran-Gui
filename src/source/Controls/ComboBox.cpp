#include <Controls/ComboBox.h>
#include <Render/Graphics.h>
#include <Helper.h>
#include <algorithm>

namespace RanGui
{
    ComboBox::ComboBox(float pos_x, float pos_y, float width, float height)
        : ControlToolTippable(pos_x, pos_y, width, height), m_selectedIndex(-1), m_hoverIndex(-1), m_scrollOffset(0), m_visibleItemCount(5), m_isDropdownVisible(false),
          m_backgroundColor(ControlColor::White),
          m_borderColor(ControlColor::Black),
          m_hoverColor(ControlColor::LightGray),
          m_arrowColor(ControlColor::Black)
    {
        m_label = std::make_unique<Label>(L"", pos_x + 5, pos_y, width - 30, height, 24.0f);
    }

    void ComboBox::Initialize(Graphics &graphics)
    {
        if (!graphics.IsValid())
            return;

        ControlToolTippable::Initialize(graphics);

        auto renderTarget = graphics.GetRenderTarget();

        renderTarget->CreateSolidColorBrush(m_backgroundColor, &m_pBackgroundBrush);
        renderTarget->CreateSolidColorBrush(m_borderColor, &m_pBorderBrush);
        renderTarget->CreateSolidColorBrush(m_hoverColor, &m_pHoverBrush);
        renderTarget->CreateSolidColorBrush(m_arrowColor, &m_pArrowBrush);

        CreateArrowGeometry(graphics);

        m_label->SetFontSize(m_height - (m_height / 2));
        m_label->Initialize(graphics);
    }

    void ComboBox::Render(Graphics &graphics)
    {
        ControlToolTippable::Render(graphics);

        if (!m_isVisible)
            return;

        DrawBackground(graphics);
        DrawBorder(graphics);
        m_label->Render(graphics);
        DrawArrow(graphics);

        if (m_isDropdownVisible)
        {
            DrawDropdown(graphics);
        }
    }

    void ComboBox::DrawBackground(Graphics &graphics)
    {
        graphics.FillRectangle(RAN_GUI_RECT(m_x, m_y, m_x + m_width, m_y + m_height), m_pBackgroundBrush.Get());
    }

    void ComboBox::DrawBorder(Graphics &graphics)
    {
        graphics.DrawRectangleRect(RAN_GUI_RECT(m_x, m_y, m_x + m_width, m_y + m_height), m_pBorderBrush.Get(), 1.0f);
    }

    void ComboBox::DrawDropdown(Graphics &graphics)
    {
        float dropdownHeight = m_height * static_cast<float>(Helper::Min(static_cast<int>(m_items.size()), m_visibleItemCount));

        graphics.FillRectangle(RAN_GUI_RECT(m_x, m_y + m_height, m_x + m_width, m_y + m_height + dropdownHeight), m_pBackgroundBrush.Get());
        graphics.DrawRectangleRect(RAN_GUI_RECT(m_x, m_y + m_height, m_x + m_width, m_y + m_height + dropdownHeight), m_pBorderBrush.Get(), 1.0f);

        int startIndex = m_scrollOffset / static_cast<int>(m_height);
        int endIndex = Helper::Min(startIndex + m_visibleItemCount, static_cast<int>(m_items.size()));

        for (int i = startIndex; i < endIndex; ++i)
        {
            if (static_cast<int>(i) == m_hoverIndex)
            {
                graphics.FillRectangle(RAN_GUI_RECT(m_x, m_y + m_height * (i - startIndex + 1), m_x + m_width, m_y + m_height * (i - startIndex + 2)), m_pHoverBrush.Get());
            }

            m_label->SetText(m_items[i]);
            m_label->SetPosition(m_x + 5, m_y + m_height + m_height * (i - startIndex));
            m_label->Render(graphics);
        }

        DrawScrollBar(graphics);

        if (m_selectedIndex != -1)
        {
            m_label->SetText(m_items[m_selectedIndex]);
            m_label->SetPosition(m_x + 5, m_y);
        }
    }

    void ComboBox::DrawScrollBar(Graphics &graphics)
    {
        float dropdownHeight = m_height * static_cast<float>(m_items.size());
        float visibleHeight = m_height * static_cast<float>(Helper::Min(static_cast<int>(m_items.size()), m_visibleItemCount));

        float scrollBarHeight = (visibleHeight / dropdownHeight) * visibleHeight;
        float scrollBarY = m_y + m_height + (static_cast<float>(m_scrollOffset) / dropdownHeight) * visibleHeight + 2;

        graphics.FillRectangle(RAN_GUI_RECT(m_x + m_width - 10, scrollBarY, m_x + m_width - 5, scrollBarY + scrollBarHeight), m_pHoverBrush.Get());
    }

    void ComboBox::UpdateScrollOffset(int delta)
    {
        int maxOffset = static_cast<int>(m_height * static_cast<float>(m_items.size() - 5));
        m_scrollOffset = std::clamp(m_scrollOffset + delta, 0, maxOffset);
    }

    void ComboBox::AddItem(const std::wstring &item)
    {
        m_items.push_back(item);
        if (m_selectedIndex == -1)
        {
            SetSelectedIndex(0);
        }
    }

    void ComboBox::SetSelectedIndex(int index)
    {
        if (index >= 0 && index < static_cast<int>(m_items.size()))
        {
            m_selectedIndex = index;
            m_label->SetText(m_items[index]);
        }
    }

    int ComboBox::GetSelectedIndex() const
    {
        return m_selectedIndex;
    }

    std::wstring ComboBox::GetSelectedItem() const
    {
        if (m_selectedIndex >= 0 && m_selectedIndex < static_cast<int>(m_items.size()))
        {
            return m_items[m_selectedIndex];
        }
        return L"";
    }

    void ComboBox::SetTextColor(const RAN_GUI_COLOR_F &color)
    {
        m_label->SetColor(color);
    }

    void ComboBox::SetFontFamilyName(const std::wstring &font)
    {
        m_label->SetFontFamilyName(font);
    }

    void ComboBox::SetBackgroundColor(const RAN_GUI_COLOR_F &color)
    {
        m_backgroundColor = color;
        Initialize(*m_graphics);
    }

    void ComboBox::SetBorderColor(const RAN_GUI_COLOR_F &color)
    {
        m_borderColor = color;
        m_arrowColor = color;
        Initialize(*m_graphics);
    }

    void ComboBox::SetHoverColor(const RAN_GUI_COLOR_F &color)
    {
        m_hoverColor = color;
        Initialize(*m_graphics);
    }

    void ComboBox::SetVisibleItemCount(int count)
    {
        m_visibleItemCount = count;
    }

    void ComboBox::SetPosition(float x, float y)
    {
        ControlToolTippable::SetPosition(x, y); 
        m_pArrowGeometry = nullptr;
    }

    void ComboBox::SetSize(float width, float height)
    {
        Renderable::SetSize(width, height);
        m_label->SetSize(width - 30, height);
        m_pArrowGeometry = nullptr;
    }

    void ComboBox::OnMouseDown(float x, float y)
    {
        if (Intersect(x, y))
        {
            m_isDropdownVisible = !m_isDropdownVisible;
        }
        else if (m_isDropdownVisible)
        {
            float dropdownHeight = m_height * static_cast<float>(m_items.size());
            if (x >= m_x && x <= m_x + m_width && y >= m_y + m_height && y <= m_y + m_height + dropdownHeight)
            {
                int index = static_cast<int>((y - m_y - m_height) / m_height) + m_scrollOffset / static_cast<int>(m_height);
                SetSelectedIndex(index);
                m_isDropdownVisible = false;
            }
            else
            {
                m_isDropdownVisible = false;
            }
        }
    }

    void ComboBox::OnMouseMove(float x, float y)
    {
        ControlToolTippable::OnMouseMove(x, y);
        
        if (m_isDropdownVisible)
        {
            m_hoverIndex = -1;
            float dropdownHeight = m_height * static_cast<float>(m_items.size());
            if (x >= m_x && x <= m_x + m_width && y >= m_y + m_height && y <= m_y + m_height + dropdownHeight)
            {
                m_hoverIndex = static_cast<int>((y - m_y - m_height) / m_height) + m_scrollOffset / static_cast<int>(m_height);
            }
        }
    }

    void ComboBox::OnMouseWheel(float delta)
    {
        if (m_isDropdownVisible)
        {
            UpdateScrollOffset(static_cast<int>(-delta));
        }
    }

    void ComboBox::DrawArrow(Graphics &graphics)
    {
        if (!m_pArrowGeometry)
        {
            CreateArrowGeometry(graphics);
        }

        auto renderTarget = graphics.GetRenderTarget();
        renderTarget->FillGeometry(m_pArrowGeometry.Get(), m_pArrowBrush.Get());
    }

    void ComboBox::CreateArrowGeometry(Graphics &graphics)
    {
        if (m_pArrowGeometry)
            return;

        auto factory = graphics.GetFactory();

        RAN_GUI_POINT points[3] = {
            RAN_GUI_POINT(m_x + m_width - 15, m_y + m_height / 2 - 5),
            RAN_GUI_POINT(m_x + m_width - 5, m_y + m_height / 2 - 5),
            RAN_GUI_POINT(m_x + m_width - 10, m_y + m_height / 2 + 5)};

        factory->CreatePathGeometry(&m_pArrowGeometry);
        Microsoft::WRL::ComPtr<ID2D1GeometrySink> pSink;

        m_pArrowGeometry->Open(&pSink);

        pSink->BeginFigure(points[0], D2D1_FIGURE_BEGIN_FILLED);
        pSink->AddLine(points[1]);
        pSink->AddLine(points[2]);
        pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

        pSink->Close();
    }
}