#pragma once

#include <Controls/Control.h>  

namespace ControlUtils
{
    void HandleMouseDown(std::vector<std::unique_ptr<RanGui::Control>>& controls, RanGui::Control*& focusedControl, float x, float y);
}