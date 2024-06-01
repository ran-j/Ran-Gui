#include <Events/EventDispatcher.h>

namespace RanGui
{
    void EventDispatcher::AddListener(std::shared_ptr<EventListener> listener)
    {
        m_listeners.push_back(listener);
    }

    void EventDispatcher::RemoveListener(std::shared_ptr<EventListener> listener)
    {
        m_listeners.erase(
            std::remove(m_listeners.begin(), m_listeners.end(), listener),
            m_listeners.end());
    }

    void EventDispatcher::Dispatch(const Event &event)
    {
        for (const auto &listener : m_listeners)
        {
            listener->OnEvent(event);
        }
    }
}