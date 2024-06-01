#pragma once
#include <vector>
#include <Events/Event.h>
#include <Events/EventListener.h>
#include <memory>

namespace RanGui
{
    class EventDispatcher
    {
    public:
        void AddListener(std::shared_ptr<EventListener> listener);
        void RemoveListener(std::shared_ptr<EventListener> listener);
        void Dispatch(const Event &event);

    private:
        std::vector<std::shared_ptr<EventListener>> m_listeners;
    };
}