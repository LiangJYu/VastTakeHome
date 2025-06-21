#include <format>
#include <iostream>
#include "MiningTruck.h"
#include "OperationClock.h"

auto main() -> int
{
    MiningSimulation::MiningTruck truck;
    MiningSimulation::OperationClock op_clock;

    while (op_clock.not_expired()) {
        if (op_clock.get_current_time() % 3600 == 0) {
            /*
            std::cout << std::format("i_hr {}, t_now {}\n",
                    op_clock.get_current_time() / 3600,
                    op_clock.get_current_time());
                    */
        }
        truck.advance_state_and_event(op_clock.get_current_time());
        ++op_clock;
    }
    return 0;
}
