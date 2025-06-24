#include "MiningTruck.h"
#include <cstdlib>

unsigned int MiningTruck::compute_mining_trip_time() const {
  return 2 * Constants::min_mining_time +
         std::rand() % Constants::mining_time_range;
}

MiningTruck::MiningTruck(unsigned int id)
    : id(id), id_assigned_station(Constants::INVALID_ID),
      state(TruckState::mining_trip), t_state_start(0), t_mining_no_transit(0),
      completion_event(TruckEvent::mining_trip_complete) {
  t_completion = 2 * Constants::transit_time + compute_mining_trip_time();
}

Event MiningTruck::advance_state_get_event(unsigned int t_now,
                                           unsigned int queue_size,
                                           unsigned int id_station) {
  if (t_now == t_completion) {
    // Compute time duration of last state.
    auto t_delta = t_now - t_state_start;

    // Update state start time.
    t_state_start = t_now;

    // Determine which state just completed.
    if (state == TruckState::mining_trip) {
      // Reset mining only time.
      t_mining_no_transit = 0;

      // Update transit and mining time.
      stats.t_transit += 2 * Constants::transit_time;
      stats.t_mining += t_delta - 2 * Constants::transit_time;

      // Advance state to station_processing.
      state = TruckState::station_processing;
      completion_event = TruckEvent::processing_complete;
      t_completion = t_state_start + (queue_size + 1) * Constants::unload_time;
      id_assigned_station = id_station;
    } else { // state == TruckState::station_processing
      // Update in_queue and unloading time, then increment trip count.
      stats.t_in_queue += t_delta - Constants::unload_time;
      stats.t_unloading += Constants::unload_time;
      stats.n_trips++;

      // Advance state to mining_trip.
      state = TruckState::mining_trip;
      completion_event = TruckEvent::mining_trip_complete;
      t_completion = t_state_start + compute_mining_trip_time();
      id_assigned_station = Constants::INVALID_ID;
    }
  }

  return get_current_event();
}

void MiningTruck::compute_incomplete_state_stats(unsigned int t_now) {
    // Compute time duration of last state.
  auto t_delta = t_now - t_state_start;

  // Determine which state is in progress.
  if (state == TruckState::mining_trip) {
    // Check if in transit to mine.
    if (t_delta < Constants::transit_time) {
      stats.t_transit += t_delta;
    // Check if mining.
    } else if (t_delta < Constants::transit_time + t_mining_no_transit) {
      stats.t_transit += Constants::transit_time;
      stats.t_mining += t_delta - Constants::transit_time;
    // Check if in transit from mine.
    } else {
      stats.t_transit += t_delta - t_mining_no_transit;
      stats.t_mining += t_mining_no_transit;
    }
  }
}
