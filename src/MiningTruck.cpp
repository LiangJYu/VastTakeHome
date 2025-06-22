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
    t_completion = Constants::transit_time + compute_mining_time();
}

unsigned int MiningTruck::compute_mining_time() const {
    srand(69);
    return Constants::min_mining_time + std::rand() % Constants::mining_time_range;
}

void MiningTruck::advance_state_and_event(unsigned int t_now,
                                          unsigned int queue_position) {
    if (t_now == t_completion) {
//        std::cout << std::format("advance_state_and_event {} ", t_now);
        auto t_delta = t_now - t_state_start;
        t_state_start = t_now;

        if (state == TruckState::transit_to_mine) {
            // Update transit time.
            stats.t_transit += Constants::transit_time;

            // Advance state.
            state = TruckState::mining;
            completion_event = TruckEvent::mining_complete;
            t_completion = t_state_start + compute_mining_time();
        }
        else if (state == TruckState::mining) {
            // Update mining time.
            stats.t_mining += t_delta;

            // Advance state.
            state = TruckState::transit_to_unload;
            completion_event = TruckEvent::station_arrival;
            t_completion = t_state_start + Constants::transit_time;
        }
        else if (state == TruckState::transit_to_unload) {
            // Update transit time.
            stats.t_transit += Constants::transit_time;

            // Advance state.
            auto unload_time = Constants::unload_time;
            auto wait_time = queue_position  * unload_time;
            state = TruckState::station_processing;
            completion_event = TruckEvent::processing_complete;
            t_completion = t_state_start + wait_time + unload_time;
        }
        else { // state == TruckState::station_processing
            // Update processing time and increment trip count.
            stats.t_in_queue += t_delta - Constants::unload_time;
            stats.t_unloading += Constants::unload_time;
            stats.n_trips++;

            // Advance state.
            state = TruckState::transit_to_mine;
            completion_event = TruckEvent::mine_arrival;
            t_completion = t_state_start + Constants::transit_time;
        }
 //       std::cout << std::format("{}\n", t_completion);
    }
}
