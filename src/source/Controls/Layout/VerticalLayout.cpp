#include <Controls/Layout/VerticalLayout.h>

namespace RanGui
{
    VerticalLayout::VerticalLayout(float pos_x, float pos_y, float width, float height, float spacing)
        : Layout(pos_x, pos_y, width, height, spacing)
    {
    }

    void VerticalLayout::Arrange()
    {
        float currentY = m_y;
        for (auto &control : m_controls)
        {
            control->SetPosition(m_x, currentY);
            currentY += control->GetHeight() + m_spacing;
        }
    }
}