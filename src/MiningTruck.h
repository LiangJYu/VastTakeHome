#ifndef MININGTRUCK_H
#define MININGTRUCK_H

#include "Constants.h"
#include "Event.h"
#include "Stats.h"

class MiningTruck {
  // ID of truck.
  unsigned int id;

  // ID of station assigned to truck for unloading. Defaults to INVALID_VALUE if
  // no station assigned. No station assigned if truck not in station_processing
  // state.
  unsigned int id_assigned_station;

  // Current state of truck.
  TruckState state;

  // Start of current state.
  unsigned int t_state_start;

  // Event type that describes completion of state.
  TruckEvent completion_event;

  // Time state ends and completion event occurrs. Used to generate Event
  // objects entered into a min-heapriority_queue that determines order of event
  // processing. Top priority_queue is the smallest/soonest Event object.
  unsigned int t_completion;

  // Length current mining procress minus tranist time. Needed for incomplete state stat computing.
  unsigned int t_mining_no_transit;

  // Collection of statistics to track truck efficiency.
  MiningTruckStats stats;

  // Randomly compute a mining time between 1 and 4 hours in seconds. Random
  // number generated in uniform.
  unsigned int compute_mining_trip_time() const;

public:
  // Constructor. Takes in ID to be assigned to truck.
  MiningTruck(unsigned int id = 0);

  // Return truck ID.
  unsigned int get_id() const { return id; }

  // Return unloading station assigned to truck.
  unsigned int get_id_assigned_station() const { return id_assigned_station; }

  // Return current state of truck.
  TruckState get_state() const { return state; }

  // Return start time of current state.
  unsigned int get_t_state_start() const { return t_state_start; }

  // Return event that describes completion of state.
  TruckEvent get_completion_event() const { return completion_event; }

  // Return time when state ends and completion event occurs.
  unsigned int get_t_completion() const { return t_completion; }

  // Return collection statistics describing truck performance in a run.
  MiningTruckStats get_stats() const { return stats; }

  // Return Event object that describes the completion of a state.
  Event get_current_event() const {
    return Event(id, completion_event, t_completion, id_assigned_station);
  }

  // Advance truck to next state. Return the completion event that describes
  // completion of next state.
  Event
  advance_state_get_event(unsigned int new_t_state_start,
                          unsigned int queue_size = 0,
                          unsigned int id_station = Constants::INVALID_ID);

  // Update stats for time done in incomplete state at end of a run.
  void compute_incomplete_state_stats(unsigned int t_now);
};

#endif // MININGTRUCK_H
