#include <Controls/Layout/HorizontalLayout.h>

namespace RanGui
{
    HorizontalLayout::HorizontalLayout(float pos_x, float pos_y, float width, float height, float spacing)
        : Layout(pos_x, pos_y, width, height, spacing)
    {
    }

    void HorizontalLayout::Arrange()
    {
        float currentX = m_x;
        for (auto &control : m_controls)
        {
            float controlY = m_y;
            switch (m_alignment)
            {
            case HorizontalLayoutAlignment::Left:
                controlY = m_y;
                break;
            case HorizontalLayoutAlignment::Center:
                controlY = m_y + (GetHeight() - control->GetHeight()) / 2;
                break;
            case HorizontalLayoutAlignment::Right:
                controlY = m_y + (GetHeight() - control->GetHeight());
                break;
            case HorizontalLayoutAlignment::None:
            default:
                break;
            }
            control->SetPosition(currentX, controlY);
            currentX += control->GetWidth() + m_spacing; // Add spacing
        }
    }
}