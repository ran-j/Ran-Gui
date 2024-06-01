#pragma once
#include <Controls/Layout/GridLayout.h>
#include <Controls/Label.h>
#include <vector>

namespace RanGui
{
    class TableLayout : public GridLayout
    {
    public:
        TableLayout(float pos_x, float pos_y, float width, float height, int rows, int cols, float spacing = 0.0f);

        void SetCell(int row, int col, std::unique_ptr<Control> control);
        void SetHeader(int col, const std::wstring &text);
        void SetColumnWidth(int col, float width);
        void SetRowHeight(int row, float height);

        void Arrange() override;

    private:
        std::vector<float> m_colWidths;
        std::vector<float> m_rowHeights;
    };
}