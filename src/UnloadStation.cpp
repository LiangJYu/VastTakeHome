#include "UnloadStation.h"

unsigned int UnloadStation::assign_truck_get_queue_pos(
        unsigned int truck_id,
        unsigned int t_now)
{
    // INVALID_ID used to indicate empty unloading bay and empty queue.
    if (id_current_truck_unloading == Constants::INVALID_ID) {
        id_current_truck_unloading = truck_id;
    } else  {
        // Loading bay not empty. Push new truck to back of queue.
        waiting_queue.push(truck_id);

        // Update stats.
        stats.add_queue_stat(waiting_queue.size(), t_now);
    }

    return static_cast<unsigned int>(waiting_queue.size());
}

unsigned int UnloadStation::truck_departure(unsigned int t_now) {
    // Assume empty bay and empty queue.
    auto id_just_departed = Constants::INVALID_ID;

    // If bay occupied, then assign truck to departing. Increment unload count.
    if (id_current_truck_unloading != Constants::INVALID_ID) {
        // Update departing ID to truck currently in bay.
        id_just_departed = id_current_truck_unloading;

        stats.n_unloads++;
    }

    // If queue not empty, assign front of queue to unloading bay, then pop it.
    if (waiting_queue.size() > 0) {
        id_current_truck_unloading = waiting_queue.front();
        waiting_queue.pop();

        // Update stats.
        stats.add_queue_stat(waiting_queue.size(), t_now);

    // Bay occupied and queue empty.
    } else if (id_current_truck_unloading != Constants::INVALID_ID) {
        // INVALID_ID used to indicate empty unloading bay and empty queue.
        id_current_truck_unloading = Constants::INVALID_ID;
    }

    return id_just_departed;
}
