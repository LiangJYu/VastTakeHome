#include "Constants.h"

namespace MiningSimulation {

class MiningTruck
{
//
TruckState state;
//
unsigned int t_state_start;
//
TruckEvent completion_event;
//
unsigned int t_completion;

//
unsigned int compute_mining_time() const;

public:
    MiningTruck();

    //
    TruckState get_state() const { return state; }
    //
    unsigned int get_t_state_start() const { return t_state_start; }
    //
    TruckEvent get_completion_event() const { return completion_event; }
    //
    unsigned int get_t_completion() const { return t_completion; }

    void advance_state_and_event(unsigned int new_t_state_start,
                                 unsigned int queue_position = 0);
};

}
