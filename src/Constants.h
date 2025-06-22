#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <limits>

namespace MiningSimulation {

/**
 * @enum Constants
 * @brief Time-related constants for clock operations.
 *
 * These constants define default timing values used by the OperationClock
 * class. All values are in seconds.
 */
struct Constants {
    // Default duration (72 hours in seconds)
    static constexpr unsigned int default_stop_time = 72 * 3600;
    // Default increment step (1 second)
    static constexpr unsigned int default_increment_time = 1;
    //
    static constexpr unsigned int transit_time = 30 * 60;
    //
    static constexpr unsigned int unload_time = 5 * 60;
    //
    static constexpr unsigned int min_mining_time = 3600;
    //
    static constexpr unsigned int mining_time_range = 4 * 3600;
    //
    static constexpr unsigned int INVALID_ID = std::numeric_limits<unsigned int>::max();
};

enum class TruckState {
    transit_to_mine,
    mining,
    transit_to_unload,
    station_processing
};

enum class TruckEvent {
    mine_arrival,
    mining_complete,
    station_arrival,
    processing_complete
};

}
 #endif // CONSTANTS_H
