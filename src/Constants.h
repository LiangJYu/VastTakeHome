namespace MiningSimulation {

/**
 * @enum TimeConstants
 * @brief Time-related constants for clock operations.
 *
 * These constants define default timing values used by the OperationClock
 * class. All values are in seconds.
 */
enum class TimeConstants : unsigned int
{
    // Default duration (72 hours in seconds)
    default_stop_time = 72 * 3600,
    // Default increment step (1 second)
    default_increment_time = 1,
    //
    transit_time = 30 * 60,
    //
    unload_time = 5 * 60
};

enum class TruckState {
    transit_to_mine,
    mining,
    transit_to_unload,
    waiting,
    unloading
};

enum class TruckEvent {
    mine_arrival,
    mining_complete,
    station_arrival,
    waiting_complete,
    unload_complete
};

}
