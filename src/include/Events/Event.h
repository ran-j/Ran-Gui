#pragma once

namespace RanGui
{
    enum class EventType
    {
        None,
        MouseDown,
        MouseUp,
        MouseMove,
        MouseEnter,
        MouseLeave,
        Click,
        Hover
    };

    class Event
    {
    public:
        Event(EventType type) : m_type(type) {}

        EventType GetType() const { return m_type; }

    private:
        EventType m_type;
    };
}