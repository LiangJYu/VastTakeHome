#include "UnloadStation.h"

unsigned int UnloadStation::assign_truck_get_queue_pos(unsigned int truck_id,
                                                       unsigned int t_now) {
  // INVALID_ID used to indicate no truck is unloading and empty queue.
  if (id_current_truck_unloading == Constants::INVALID_ID) {
    id_current_truck_unloading = truck_id;
  } else {
    // Another truck currently unloading. Push new truck to back of queue.
    waiting_queue.push(truck_id);

    // Update stats.
    stats.add_queue_stat(waiting_queue.size(), t_now);
  }

  return static_cast<unsigned int>(waiting_queue.size());
}

unsigned int UnloadStation::dispatch_truck(unsigned int t_now) {
  // Assume no truck is unloading and empty queue.
  auto id_just_departed = Constants::INVALID_ID;

  // Check if truck currently unloading.
  if (id_current_truck_unloading != Constants::INVALID_ID) {
    // Update departing ID to truck currently unloading.
    id_just_departed = id_current_truck_unloading;

    // Increment unload count.
    stats.n_unloads++;
  }

  // Check if queue not empty.
  if (waiting_queue.size() > 0) {
    // Assign front of queue to unloading, then pop it from queue.
    id_current_truck_unloading = waiting_queue.front();
    waiting_queue.pop();

    // Add change in queue size and time of change.
    stats.add_queue_stat(waiting_queue.size(), t_now);
  } else { // Queue empty
    // INVALID_ID used to indicate empty unloading bay and empty queue.
    id_current_truck_unloading = Constants::INVALID_ID;
  }

  return id_just_departed;
}
