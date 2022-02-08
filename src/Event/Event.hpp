

#ifndef TEMPLATEPROJECT_EVENT_HPP
#define TEMPLATEPROJECT_EVENT_HPP
enum class EventType{
    None = 0
};
enum class EventCategory {
    None = 0;
    //app
    //mouse
    //cb
    //input
};
class Event{
    //friend class eventDispatcher
public:
    //get type
    //get name
    //get name
    //get category
private:
    bool _handled = false;
};

class EventDispatcher;

#endif //TEMPLATEPROJECT_EVENT_HPP
