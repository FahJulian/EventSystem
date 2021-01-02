# EventSystem

Simple EventSystem in C++
Only contains a header file because of templates requiring implementations in the header file.

The Observer (The class that creates Events of a certain type) has an EventDispatcher.
Subjects (The classes that listen to the Events) then Add their EventListeners to the 
EventDispatcher. The EventDispatcher then Dispatches the Events to the Listeners.
