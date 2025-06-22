#ifndef UNLOADSTATION_H
#define UNLOADSTATION_H

#include <queue>
#include "Constants.h"

class UnloadStation
{
unsigned int id;
unsigned int id_current_truck_unloading;
std::queue<unsigned int> waiting_queue;

public:
    UnloadStation(unsigned int id = Constants::INVALID_ID)
        : id(id)
        , id_current_truck_unloading(Constants::INVALID_ID) {};

    unsigned int get_id() const { return id; }

    std::size_t get_queue_length() const { return waiting_queue.size(); }

    unsigned int get_wait_time() const {
        return static_cast<unsigned int>(waiting_queue.size()) * Constants::unload_time;
    }

    unsigned int get_current_truck_id() { return id_current_truck_unloading; }

    unsigned int assign_truck_get_queue_pos(unsigned int truck_id);

    unsigned int truck_departure();
};

#endif // UNLOADSTATION_H
