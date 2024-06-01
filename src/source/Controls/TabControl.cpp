#include <Controls/TabControl.h>
#include <Render/Graphics.h>

namespace RanGui
{
    TabPage::TabPage(const std::wstring &title)
        : Control(0.f, 0.f, 0.f, 0.f), m_title(title)
    {
    }

    void TabPage::Render(Graphics &graphics)
    {
        m_content->Render(graphics);
    }

    const std::wstring &TabPage::GetTitle() const
    {
        return m_title;
    }

    void TabPage::SetContent(std::unique_ptr<Control> content)
    {
        m_content = std::move(content);
    }

    Control *TabPage::GetContent() const
    {
        return m_content.get();
    }

    TabControl::TabControl(float pos_x, float pos_y, float width, float height)
        : Control(pos_x, pos_y, width, height),
          m_activeTab(0),
          m_tabTextColor(ControlColor::Black),
          m_tabBackgroundColor(ControlColor::LightGray),
          m_tabBorderColor(ControlColor::Black),
          m_contentBackgroundColor(ControlColor::White)
    {
    }

    void TabControl::Initialize(Graphics &graphics)
    {
        if (!graphics.IsValid())
            return;

        auto renderTarget = graphics.GetRenderTarget();
        auto dwriteFactory = graphics.GetWriteFactory();

        renderTarget->CreateSolidColorBrush(m_tabTextColor, &m_pTabTextBrush);
        renderTarget->CreateSolidColorBrush(m_tabBackgroundColor, &m_pTabBackgroundBrush);
        renderTarget->CreateSolidColorBrush(m_tabBorderColor, &m_pTabBorderBrush);
        renderTarget->CreateSolidColorBrush(m_contentBackgroundColor, &m_pContentBackgroundBrush);

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

        for (auto &tab : m_tabs)
        {
            if (tab->GetContent())
            {
                tab->GetContent()->Initialize(graphics);
            }
        }
    }

    void TabControl::Render(Graphics &graphics)
    {
        if (!m_isVisible)
            return;

        auto renderTarget = graphics.GetRenderTarget();

        float tabHeight = 30.0f;
        float tabWidth = m_width / m_tabs.size();

        for (size_t i = 0; i < m_tabs.size(); ++i)
        {
            float x = m_x + i * tabWidth;
            float y = m_y;

            RAN_GUI_RECT tabRect = RAN_GUI_RECT(x, y, x + tabWidth, y + tabHeight);
            graphics.FillRectangle(tabRect, m_pTabBackgroundBrush.Get());
            graphics.DrawRectangleRect(tabRect, m_pTabBorderBrush.Get());

            renderTarget->DrawTextW(
                m_tabs[i]->GetTitle().c_str(),
                static_cast<UINT32>(m_tabs[i]->GetTitle().length()),
                m_pTextFormat.Get(),
                tabRect,
                m_pTabTextBrush.Get());
        }

        RAN_GUI_RECT contentRect = RAN_GUI_RECT(m_x, m_y + tabHeight, m_x + m_width, m_y + m_height);
        graphics.FillRectangle(contentRect, m_pContentBackgroundBrush.Get());

        if (m_tabs[m_activeTab]->GetContent())
        {
            m_tabs[m_activeTab]->GetContent()->SetPosition(m_x, m_y + tabHeight);
            m_tabs[m_activeTab]->GetContent()->SetSize(m_width, m_height - tabHeight);
            m_tabs[m_activeTab]->GetContent()->Render(graphics);
        }
    }

    void TabControl::AddTab(std::unique_ptr<TabPage> tab)
    {
        m_tabs.push_back(std::move(tab));
    }

    void TabControl::SetActiveTab(int index)
    {
        if (index >= 0 && index < static_cast<int>(m_tabs.size()))
        {
            m_activeTab = index;
        }
    }

    void TabControl::SetFontFamilyName(const std::wstring &font)
    {
        m_font = font;
        Initialize(*m_graphics);
    }

    int TabControl::GetActiveTab() const
    {
        return m_activeTab;
    }

    void TabControl::SetTabTextColor(const RAN_GUI_COLOR_F &color)
    {
        m_tabTextColor = color;
        Initialize(*m_graphics);
    }

    void TabControl::SetTabBackgroundColor(const RAN_GUI_COLOR_F &color)
    {
        m_tabBackgroundColor = color;
        Initialize(*m_graphics);
    }

    void TabControl::SetTabBorderColor(const RAN_GUI_COLOR_F &color)
    {
        m_tabBorderColor = color;
        Initialize(*m_graphics);
    }

    void TabControl::SetContentBackgroundColor(const RAN_GUI_COLOR_F &color)
    {
        m_contentBackgroundColor = color;
        Initialize(*m_graphics);
    }

    void TabControl::OnMouseDown(float x, float y)
    {
        if (y >= m_y && y <= m_y + 30.0f)
        {
            float tabWidth = m_width / m_tabs.size();
            int index = static_cast<int>((x - m_x) / tabWidth);
            SetActiveTab(index);
        }
    }
}
