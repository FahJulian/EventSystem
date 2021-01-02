#include <iostream>
#include "EventDispatcher.h"


class Event
{
public:
    const char* dsrc;
};


class Layer
{
public:
    Layer()
    {
        eventDispatcher.AddListener<Layer, Layer::OnEvent>(this);
    }

    void OnEvent(const Event& event)
    {
        std::cout << event.dsrc << std::endl;
    }
};


void onEvent(const Event& event)
{
    std::cout << "Func: " << event.dsrc << std::endl;
}


static EventDispatcher<Event> eventDispatcher;

int main()
{
    Layer layer;
    eventDispatcher.AddListener(onEvent);
    eventDispatcher.Dispatch({ "Test Event" });
}
