#pragma once
#include <Controls/Layout/Layout.h>

namespace RanGui
{
    enum class HorizontalLayoutAlignment
    {
        None,
        Left,
        Center,
        Right
    };

    class HorizontalLayout : public Layout
    {
    protected:
        HorizontalLayoutAlignment m_alignment = HorizontalLayoutAlignment::None;

    public:
        HorizontalLayout(float pos_x, float pos_y, float width, float height, float spacing = 0.0f);
        virtual void Arrange() override;

    public:
        void SetAlignment(HorizontalLayoutAlignment alignment) { m_alignment = alignment; }
        HorizontalLayoutAlignment GetAlignment() const { return m_alignment; }
    };
}