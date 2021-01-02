#include <vector>
#include "EventListener.h"

template<typename E>
class EventDispatcher
{
private:
    template<typename T>
    using EventListenerFunction = void(*)(const T&);

    template<typename E>
    struct EventListenerMethod
    {
        void* const object;
        void(*function)(void* const, const E&);

        EventListenerMethod(void* const object, void(*function)(void* const, const E&))
            : object(object), function(function)
        {
        }

        void operator()(const E& event)
        {
            function(object, event);
        }
    };

public:
    void AddListener(const EventListenerFunction<E>& listener)
    {
        m_Functions.emplace_back(listener);
    }
    
    template<typename F, void(F::*M)(const E&)>
    void AddListener(F* const object)
    {
        m_Methods.emplace_back(
            object, 
            [](void* const p, const E& event){ 
                // Cast the void* back to F* and then call the event method on it
                (static_cast<F* const>(p)->*M)(event); 
            }
        );
    }

    void Dispatch(const E& event)
    {
        for (int i = 0; i < m_Methods.size(); i++)
            m_Methods.at(i)(event);

        for (int i = 0; i < m_Functions.size(); i++)
            m_Functions.at(i)(event);
    }

private:
    std::vector<EventListenerMethod<E>> m_Methods;
    std::vector<EventListenerFunction<E>> m_Functions;
};
