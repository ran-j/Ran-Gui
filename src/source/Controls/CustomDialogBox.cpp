#include <Controls/CustomDialogBox.h>
#include <Render/Graphics.h>

namespace RanGui
{
    CustomDialogBox::CustomDialogBox(float pos_x, float pos_y, float width, float height)
        : Panel(pos_x, pos_y, width, height), m_buttonHeight(40.f)
    {
    }

    void CustomDialogBox::SetTitle(const std::wstring &title)
    {
        m_title = title;
    }

    void CustomDialogBox::SetMessage(const std::wstring &message)
    {
        m_message = message;
    }

    void CustomDialogBox::AddButton(const std::wstring &text, std::function<void()> onClick)
    {
        m_buttons.emplace_back(text, onClick);
    }

    void CustomDialogBox::Initialize(Graphics &graphics)
    {
        Panel::Initialize(graphics);

        m_titleLabel = std::make_unique<Label>(m_title, m_x + 10.f, m_y + 10.f, m_width - 20.f, 30.f);
        m_titleLabel->Initialize(graphics);

        m_messageLabel = std::make_unique<Label>(m_message, m_x + 10.f, m_y + 50.f, m_width - 20.f, m_height - 100.f);
        m_messageLabel->Initialize(graphics);

        float buttonWidth = (m_width - 20.f) / m_buttons.size();
        float buttonY = m_y + m_height - m_buttonHeight - 10.f;

        for (size_t i = 0; i < m_buttons.size(); ++i)
        {
            auto button = std::make_unique<Button>(m_buttons[i].first, m_x + 10 + i * buttonWidth, buttonY, buttonWidth - 10, m_buttonHeight);
            button->Initialize(graphics);

            auto listener = std::make_shared<RanGui::LambdaEventListener>(EventType::Click, [this, i](const Event &event)
                                                                          {
            if (event.GetType() == EventType::Click)
            {
                m_buttons[i].second();
            } });

            button->AddEventListener(listener);

            AddControl(std::move(button), true);
        }
    }

    void CustomDialogBox::Render(Graphics &graphics)
    {
        Panel::Render(graphics);

        if (m_titleLabel)
        {
            m_titleLabel->Render(graphics);
        }

        if (m_messageLabel)
        {
            m_messageLabel->Render(graphics);
        }
    }

    void CustomDialogBox::SetPosition(float x, float y)
    {
        Panel::SetPosition(x, y);

        if (m_titleLabel)
        {
            m_titleLabel->SetPosition(x + 10.f, y + 10.f);
        }

        if (m_messageLabel)
        {
            m_messageLabel->SetPosition(x + 10.f, y + 50.f);
        }
 
        for (size_t i = 0; i < m_buttons.size(); ++i)
        {
            float buttonWidth = (m_width - 20.f) / m_buttons.size(); 
            float buttonY = m_y + m_height - m_buttonHeight - 10.f;

            auto &button = m_controls[i];
            button->SetPosition(m_x + 10 + i * buttonWidth, buttonY);
        }
    }

}
