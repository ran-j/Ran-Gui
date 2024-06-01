#pragma once
#include <Controls/Layout/Layout.h>
#include <map>

namespace RanGui
{
    class GridLayout : public Layout
    {
    public:
        struct GridItem
        {
            Control *control;
            int row;
            int col;
            int rowSpan;
            int colSpan;
        };

        GridLayout(float pos_x, float pos_y, float width, float height, int rows, int cols, float spacing = 0.0f);

        void AddControl(std::unique_ptr<Control> control, int row, int col, int rowSpan = 1, int colSpan = 1);
        virtual void Arrange() override;

    protected:
        int m_rows;
        int m_cols;
        float m_spacing;
        std::map<Control *, GridItem> m_grid_controls;
    };
}