#pragma once
#include <Events/Event.h>
#include <unordered_map>
#include <functional>
#include <memory>

namespace RanGui
{
    using EventHandler = std::function<void(const Event &)>;

    class EventListener
    {
    public:
        virtual ~EventListener() = default;
        virtual void OnEvent(const Event &event) = 0;
    };

    class LambdaEventListener : public EventListener
    {
    private:
        std::unordered_map<EventType, EventHandler> m_eventHandlers;

    public:
        LambdaEventListener() = default;
        LambdaEventListener(EventHandler handler)
        {
            AddEventHandler(EventType::None, handler);
        }
        LambdaEventListener(EventType type, EventHandler handler)
        {
            AddEventHandler(type, handler);
        }

        virtual void OnEvent(const Event &event) override
        {
            HandleEvent(event);
        }

        void AddEventHandler(EventType type, EventHandler handler)
        {
            m_eventHandlers[type] = std::move(handler);
        }

        void HandleEvent(const Event &event)
        {
            auto it = m_eventHandlers.find(event.GetType());
            if (it != m_eventHandlers.end())
            {
                if (it->first == event.GetType() || it->first == EventType::None)
                    it->second(event);
            }
        }
    };
}
