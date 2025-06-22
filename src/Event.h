#ifndef EVENT_H
#define EVENT_H

#include "Constants.h"

class Event
{
    unsigned int truck_id;
    //
    TruckEvent completion_event;
    //
    unsigned int t_completion;

public:
    Event(unsigned int id, TruckEvent event, unsigned int t)
        : truck_id(id)
        , completion_event(event)
        , t_completion(t) {}

    unsigned int get_id() const { return truck_id; }

    TruckEvent get_completion_event() const { return completion_event; }

    unsigned int get_t_completion() const {return t_completion; }

    bool operator>(const Event& other_event) const
    {
        return t_completion > other_event.t_completion;
    }
};

#endif // EVENT_H
