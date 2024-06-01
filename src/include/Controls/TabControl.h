#pragma once
#include <Controls/Control.h>
#include <vector>
#include <string>
#include <memory>

namespace RanGui
{
    class TabPage : public Control
    {
    public:
        TabPage(const std::wstring &title);

    public:
        virtual void Render(Graphics &graphics) override;

    public:
        const std::wstring &GetTitle() const;
        void SetContent(std::unique_ptr<Control> content);
        Control *GetContent() const;

    private:
        std::wstring m_title;
        std::unique_ptr<Control> m_content;
    };

    class TabControl : public Control
    {
    public:
        TabControl(float pos_x, float pos_y, float width, float height);

        virtual void Render(Graphics &graphics) override;
        virtual void Initialize(Graphics &graphics) override;

        void AddTab(std::unique_ptr<TabPage> tab);
        void SetActiveTab(int index);
        int GetActiveTab() const;

        void SetTabTextColor(const RAN_GUI_COLOR_F &color);
        void SetTabBackgroundColor(const RAN_GUI_COLOR_F &color);
        void SetTabBorderColor(const RAN_GUI_COLOR_F &color);
        void SetContentBackgroundColor(const RAN_GUI_COLOR_F &color);

        void SetFontFamilyName(const std::wstring &font);

        void OnMouseDown(float x, float y) override;

    private:
        std::wstring m_font = L"Arial";
        std::vector<std::unique_ptr<TabPage>> m_tabs;
        int m_activeTab;
        RAN_GUI_COLOR_F m_tabTextColor;
        RAN_GUI_COLOR_F m_tabBackgroundColor;
        RAN_GUI_COLOR_F m_tabBorderColor;
        RAN_GUI_COLOR_F m_contentBackgroundColor;

        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pTabTextBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pTabBackgroundBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pTabBorderBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pContentBackgroundBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_TEXT_FORMAT> m_pTextFormat;
    };
}