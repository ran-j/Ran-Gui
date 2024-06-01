#pragma once
#include <Events/Event.h>

namespace RanGui
{
    class MouseEvent : public Event
    {
    public:
        MouseEvent(EventType type, float x, float y)
            : Event(type), m_x(x), m_y(y) {}

        float GetX() const { return m_x; }
        float GetY() const { return m_y; }

    private:
        float m_x;
        float m_y;
    };
}