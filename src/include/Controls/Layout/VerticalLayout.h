#pragma once

#include <Controls/Layout/Layout.h>

namespace RanGui
{
    class VerticalLayout : public Layout
    {
    public:
        VerticalLayout(float pos_x, float pos_y, float width, float height, float spacing = 0.0f);
        virtual void Arrange() override;
    };
}