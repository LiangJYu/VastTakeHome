#include <cstdlib>
#include <format>
#include <iostream>
#include "MiningTruck.h"

MiningTruck::MiningTruck(unsigned int id) :
    id(id),
    state(TruckState::mining),
    completion_event(TruckEvent::mining_complete),
    t_state_start(0)
{
    t_completion = compute_mining_time();
}

unsigned int MiningTruck::compute_mining_time() const {
    srand(69);
    return Constants::min_mining_time + std::rand() % Constants::mining_time_range;
}

void MiningTruck::advance_state_and_event(unsigned int t_now,
                                          unsigned int queue_position) {
    if (t_now == t_completion) {
//        std::cout << std::format("advance_state_and_event {} ", t_now);
        t_state_start = t_now;

        if (state == TruckState::transit_to_mine) {
            state = TruckState::mining;
            completion_event = TruckEvent::mining_complete;
            t_completion = t_state_start + compute_mining_time();
        }
        else if (state == TruckState::mining) {
            state = TruckState::transit_to_unload;
            completion_event = TruckEvent::station_arrival;
            t_completion = t_state_start + Constants::transit_time;
        }
        else if (state == TruckState::transit_to_unload) {
            auto unload_time = Constants::unload_time;
            auto wait_time = queue_position  * unload_time;
            state = TruckState::station_processing;
            completion_event = TruckEvent::processing_complete;
            t_completion = t_state_start + wait_time + unload_time;
        }
        else {
            state = TruckState::transit_to_mine;
            completion_event = TruckEvent::mine_arrival;
            t_completion = t_state_start + Constants::transit_time;
        }
 //       std::cout << std::format("{}\n", t_completion);
    }
}
