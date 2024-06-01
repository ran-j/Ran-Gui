#pragma once
#include <Controls/ControlToolTippable.h>
#include <Controls/Label.h>
#include <string>
#include <vector>

namespace RanGui
{
    class ComboBox : public ControlToolTippable
    {
    public:
        ComboBox(float pos_x, float pos_y, float width, float height);

    public:
        virtual void Render(Graphics &graphics) override;
        virtual void Initialize(Graphics &graphics) override;

    public:
        void AddItem(const std::wstring &item);
        void SetSelectedIndex(int index);
        int GetSelectedIndex() const;
        std::wstring GetSelectedItem() const;

    public:
        void SetTextColor(const RAN_GUI_COLOR_F &color);
        void SetFontFamilyName(const std::wstring &font);
        void SetBackgroundColor(const RAN_GUI_COLOR_F &color);
        void SetBorderColor(const RAN_GUI_COLOR_F &color);
        void SetHoverColor(const RAN_GUI_COLOR_F &color);

    public:
        void SetVisibleItemCount(int count);

    public:
        void OnMouseDown(float x, float y) override;
        void OnMouseMove(float x, float y) override;
        void OnMouseWheel(float delta) override;

        virtual void SetPosition(float x, float y) override;
        virtual void SetSize(float width, float height) override;

    private:
        std::vector<std::wstring> m_items;
        int m_selectedIndex;
        int m_hoverIndex;
        int m_scrollOffset;
        int m_visibleItemCount;
        bool m_isDropdownVisible;

        RAN_GUI_COLOR_F m_backgroundColor;
        RAN_GUI_COLOR_F m_borderColor;
        RAN_GUI_COLOR_F m_hoverColor;
        RAN_GUI_COLOR_F m_arrowColor;

        std::unique_ptr<Label> m_label;

        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBackgroundBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pBorderBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pHoverBrush;
        Microsoft::WRL::ComPtr<RAN_GUI_SOLID_COLOR_BRUSH> m_pArrowBrush;

        Microsoft::WRL::ComPtr<RAN_GUI_PATH_GEOMETRY> m_pArrowGeometry;

        void CreateArrowGeometry(Graphics &graphics);

        void DrawBackground(Graphics &graphics);
        void DrawBorder(Graphics &graphics);
        void DrawDropdown(Graphics &graphics);
        void DrawArrow(Graphics &graphics);
        void DrawScrollBar(Graphics &graphics);
        void UpdateScrollOffset(int delta);
    };
}