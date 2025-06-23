#ifndef EVENT_H
#define EVENT_H

#include "Constants.h"

class Event {
  // ID of truck in event.
  unsigned int truck_id;

  // ID of station in event. Defaults to INVALID_VALUE if no station associated
  // with event.
  unsigned int station_id;

  // Description of event.
  TruckEvent event_type;

  // Time the event completes.
  unsigned int t_completion;

public:
  Event(unsigned int t_id, TruckEvent event, unsigned int t,
        unsigned int s_id = Constants::INVALID_ID)
      : truck_id(t_id), station_id(s_id), event_type(event), t_completion(t) {}

  unsigned int get_truck_id() const { return truck_id; }

  unsigned int get_station_id() const { return station_id; }

  TruckEvent get_type() const { return event_type; }

  unsigned int get_t_completion() const { return t_completion; }

  // Needed for min-heap priority_queue of events.
  bool operator>(const Event &other_event) const {
    return t_completion > other_event.t_completion;
  }
};

#endif // EVENT_H
