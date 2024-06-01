#pragma once
#include <Controls/Panel.h>
#include <Controls/Button.h>
#include <Controls/Label.h>
#include <functional>

namespace RanGui
{
    class CustomDialogBox : public Panel
    {
    public:
        CustomDialogBox(float pos_x, float pos_y, float width, float height);

        void SetTitle(const std::wstring &title);
        void SetMessage(const std::wstring &message);
        void AddButton(const std::wstring &text, std::function<void()> onClick);

    public:
        virtual void Initialize(Graphics &graphics) override;
        virtual void Render(Graphics &graphics) override;

    public:
        virtual void SetPosition(float x, float y) override;

    private:
        float m_buttonHeight;
        std::wstring m_title;
        std::wstring m_message;
        std::vector<std::pair<std::wstring, std::function<void()>>> m_buttons;
        std::unique_ptr<Label> m_titleLabel;
        std::unique_ptr<Label> m_messageLabel;
    };
}
