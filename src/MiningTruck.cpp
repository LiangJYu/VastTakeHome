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
    auto dt_state = t_now - t_state_start;

    // Update state start time.
    t_state_start = t_now;

    // Determine which state just completed.
    if (state == TruckState::mining_trip) {
      // Reset mining only time.
      t_mining_no_transit = 0;

      // Update transit and mining time.
      stats.t_transit += 2 * Constants::transit_time;
      stats.t_mining += dt_state - 2 * Constants::transit_time;

      // Advance state to station_processing.
      state = TruckState::station_processing;
      completion_event = TruckEvent::unload_complete;
      t_completion = t_state_start + (queue_size + 1) * Constants::unload_time;
      id_assigned_station = id_station;

    } else { // state == TruckState::station_processing
      // Update in_queue and unloading time, then increment trip count.
      stats.t_in_queue += dt_state - Constants::unload_time;
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
  auto dt_incomplete_state = t_now - t_state_start;

  // Determine which state is in progress.
    // Check if in mining trip.
  if (state == TruckState::mining_trip) {
    // Check if in transit to mine.
    if (dt_incomplete_state < Constants::transit_time) {
      stats.t_transit += dt_incomplete_state;

    // Check if mining.
    } else if (dt_incomplete_state < Constants::transit_time + t_mining_no_transit) {
      stats.t_transit += Constants::transit_time;
      stats.t_mining += dt_incomplete_state - Constants::transit_time;
    }

  // Otherwise in station processing.
  } else {
    stats.t_transit += dt_incomplete_state - t_mining_no_transit;
    stats.t_mining += t_mining_no_transit;

    // Compute total expected time in processing state.
    const auto dt_expected_proc = t_completion - t_state_start;

    // Compute expected time in queue in processing state.
    const auto dt_expected_queue = dt_expected_proc - Constants::unload_time;

    // Below logic works regardless if truck was in queue or not.
    // Check if in queue.
    if (dt_incomplete_state < dt_expected_queue) {
      stats.t_in_queue += dt_incomplete_state;

    // Update stats if unloading.
    } else {
      stats.t_in_queue += dt_expected_queue;
      stats.t_unloading += dt_incomplete_state - dt_expected_queue;
    }
  }
}
