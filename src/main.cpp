#include <iostream>
#include "EventDispatcher.h"

static Sonic::EventDispatcher s_EventDispatcher;

class Event
{
public:
    const char* dsrc;
};

class Class1
{
public:
    Class1()
    {
        s_EventDispatcher.AddListener(this, &Class1::OnEvent);
    }

    void OnEvent(const Event& event)
    {
        std::cout << "Class 1: " << event.dsrc << std::endl;
    }
};

class Class2
{
public:
    Class2()
    {
        s_EventDispatcher.AddKeyedListener(this, &Class2::OnEvent);
    }

    void OnEvent(const Event& event)
    {
        std::cout << "Class 2: " << event.dsrc << std::endl;
    }

    ~Class2()
    {
        s_EventDispatcher.RemoveKeyedListener<Event>(this);
    }
};

void onEvent(const Event& event)
{
    std::cout << "Func: " << event.dsrc << std::endl;
}


int main()
{
    Class1 class1;
    Class2* class2 = new Class2();
    s_EventDispatcher.AddListener<Event>(onEvent);

    s_EventDispatcher.DispatchEvent<Event>({ "Test Event" });

    delete class2;
    
    s_EventDispatcher.DispatchEvent<Event>({ "Test Event" });
}
