#include <Controls/Layout/TableLayout.h>
#include <Controls/Control.h>

namespace RanGui
{
    TableLayout::TableLayout(float pos_x, float pos_y, float width, float height, int rows, int cols, float spacing)
        : GridLayout(pos_x, pos_y, width, height, rows, cols, spacing),
          m_colWidths(cols, (width - (cols - 1) * spacing) / cols),
          m_rowHeights(rows, (height - (rows - 1) * spacing) / rows)
    {
    }

    void TableLayout::SetCell(int row, int col, std::unique_ptr<Control> control)
    {
        AddControl(std::move(control), row, col);
    }

    void TableLayout::SetHeader(int col, const std::wstring &text)
    {
        auto label = std::make_unique<Label>(text, 0.f, 0.f, m_colWidths[col], m_rowHeights[0]);
        label->SetAlignment(TextAlignment::Center);
        SetCell(0, col, std::move(label));
    }

    void TableLayout::SetColumnWidth(int col, float width)
    {
        m_colWidths[col] = width;
    }

    void TableLayout::SetRowHeight(int row, float height)
    {
        m_rowHeights[row] = height;
    }

    void TableLayout::Arrange()
    {
        float y = m_y;
        for (int row = 0; row < m_rows; ++row)
        {
            float x = m_x;
            for (int col = 0; col < m_cols; ++col)
            {
                auto it = std::find_if(m_grid_controls.begin(), m_grid_controls.end(),
                                       [=](const std::pair<Control *, GridItem> &item)
                                       { return item.second.row == row && item.second.col == col; });

                if (it != m_grid_controls.end())
                {
                    float width = m_colWidths[col] * it->second.colSpan + (it->second.colSpan - 1) * m_spacing;
                    float height = m_rowHeights[row] * it->second.rowSpan + (it->second.rowSpan - 1) * m_spacing;
                    it->second.control->SetPosition(x, y);
                    it->second.control->SetSize(width, height);
                    it->second.control->Initialize(*m_graphics);
                }
                x += m_colWidths[col] + m_spacing;
            }
            y += m_rowHeights[row] + m_spacing;
        }
    }
}