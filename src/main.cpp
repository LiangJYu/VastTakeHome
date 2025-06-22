#include <format>
#include <iostream>
#include "MiningTruck.h"
#include "OperationClock.h"
#include "UnloadStation.h"

auto main() -> int
{
    OperationClock op_clock;
    MiningTruck truck;
    UnloadStation unload_station;

    while (op_clock.not_expired()) {
        if (op_clock.get_current_time() % 3600 == 0) {
            /*
            std::cout << std::format("i_hr {}, t_now {}\n",
                    op_clock.get_current_time() / 3600,
                    op_clock.get_current_time());
                    */
        }

        truck.advance_state_and_event(op_clock.get_current_time());

        if (truck.get_state() == TruckState::station_processing) {
            auto queue_pos = unload_station.assign_truck_get_queue_pos(truck.get_id());
        }

        ++op_clock;
    }
    return 0;
}
