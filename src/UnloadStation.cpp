#include "UnloadStation.h"

namespace MiningSimulation {

unsigned int UnloadStation::assign_truck_get_queue_pos(
        unsigned int truck_id)
{
    if (id_current_truck_unloading == Constants::INVALID_ID) {
        id_current_truck_unloading = truck_id;
    } else  {
        waiting_queue.push(truck_id);
    }

    return static_cast<unsigned int>(waiting_queue.size());
}

unsigned int UnloadStation::truck_departure() {
    auto id_just_departed = id_current_truck_unloading;
    if (waiting_queue.size() > 0) {
        id_current_truck_unloading = waiting_queue.front();
        waiting_queue.pop();
    } else {
        id_current_truck_unloading = Constants::INVALID_ID;
    }
    return id_just_departed;
}

}
