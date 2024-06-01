#include <Controls/ControlUtils.h>

void ControlUtils::HandleMouseDown(std::vector<std::unique_ptr<RanGui::Control>> &controls, RanGui::Control *&focusedControl, float x, float y)
{
    RanGui::Control *newFocusedControl = nullptr;

    for (auto &control : controls)
    {
        control->OnMouseDown(x, y);

        if (!newFocusedControl && control->Intersect(x, y))
        {
            newFocusedControl = control.get();
        }
    }

    if (newFocusedControl != focusedControl)
    {
        focusedControl = newFocusedControl;

        for (auto &control : controls)
        {
            control->OnFocus(control.get() == focusedControl);
        }
    }
    else
    {
        if (focusedControl)
            focusedControl->OnFocus(true);
    }
}