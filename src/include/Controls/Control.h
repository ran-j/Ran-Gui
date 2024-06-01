#pragma once
#include <Render/Renderable.h>
#include <Events/EventListener.h>
#include <vector>
#include <memory>

namespace RanGui
{
    class Control : public Renderable
    {
    public:
        Control(float pos_x, float pos_y, float width, float height)
            : Renderable(pos_x, pos_y, width, height) {}

    public:
        virtual void OnMouseMove(float x, float y);
        virtual void OnMouseDown(float x, float y);
        virtual void OnMouseUp(float x, float y);
        virtual void OnMouseWheel(float delta);
        virtual void OnKeyDown(WPARAM key);
        virtual void OnChar(WPARAM ch);
        virtual void OnFocus(bool focused);

    public:
        void AddEventListener(std::shared_ptr<EventListener> listener);
        void RemoveEventListener(std::shared_ptr<EventListener> listener);

    public:
        bool IsFocused() const;

    protected:
        void DispatchEvent(const Event &event);

    protected:
        std::vector<std::shared_ptr<EventListener>> m_eventListeners;
        bool m_isFocused = false;
        bool m_isHover = false;
    };
}