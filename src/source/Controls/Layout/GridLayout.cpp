#include <Controls/Layout/GridLayout.h>

namespace RanGui
{
    GridLayout::GridLayout(float pos_x, float pos_y, float width, float height, int rows, int cols, float spacing)
        : Layout(pos_x, pos_y, width, height), m_rows(rows), m_cols(cols), m_spacing(spacing)
    {
    }

    void GridLayout::AddControl(std::unique_ptr<Control> control, int row, int col, int rowSpan, int colSpan)
    {
        if (row < m_rows && col < m_cols && rowSpan > 0 && colSpan > 0)
        {
            Layout::AddControl(std::move(control));
            auto lastControl = GetLastControl();
            auto &item = m_grid_controls[lastControl];
            item.row = row;
            item.col = col;
            item.rowSpan = rowSpan;
            item.colSpan = colSpan;
            item.control = lastControl;
        }
    }

    void GridLayout::Arrange()
    {
        if (m_grid_controls.empty())
            return;

        float cellWidth = (m_width - (m_cols - 1) * m_spacing) / m_cols;
        float cellHeight = (m_height - (m_rows - 1) * m_spacing) / m_rows;

        for (auto &item : m_grid_controls)
        {
            float x = m_x + item.second.col * (cellWidth + m_spacing);
            float y = m_y + item.second.row * (cellHeight + m_spacing);
            float width = item.second.colSpan * cellWidth + (item.second.colSpan - 1) * m_spacing;
            float height = item.second.rowSpan * cellHeight + (item.second.rowSpan - 1) * m_spacing;

            item.second.control->SetPosition(x, y);
            item.second.control->SetSize(width, height);
            item.second.control->Initialize(*m_graphics);
        }
    }
}