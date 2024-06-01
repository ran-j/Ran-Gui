#pragma once
#include <Controls/Control.h>
#include <vector>
#include <memory>

namespace RanGui
{
    class Layout : public Control
    {
    public:
        Layout(float x, float y, float width, float height, float spacing = 0.0f);
        virtual ~Layout() = default;

        virtual void AddControl(std::unique_ptr<Control> control);
        Control *GetLastControl() const;

        virtual void Arrange() = 0;

        virtual void Render(Graphics &graphics) override;
        virtual void Initialize(Graphics &graphics) override;

    public:
        virtual void OnMouseMove(float x, float y) override;
        virtual void OnMouseDown(float x, float y) override;
        virtual void OnMouseUp(float x, float y) override;
        virtual void OnMouseWheel(float delta) override;
        virtual void OnKeyDown(WPARAM key) override;
        virtual void OnChar(WPARAM ch) override;

    protected:
        std::vector<std::unique_ptr<Control>> m_controls;
        float m_spacing;

    private:
        Control *m_focusedControl;
    };
}