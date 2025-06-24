#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <limits>

/**
 * @enum Constants
 * @brief Time-related constants for clock operations.
 *
 * These constants define default timing values used by the OperationClock
 * class. All values are in s.
 */
struct Constants {
  // Default duration (72 hours in minutes)
  static constexpr unsigned int default_stop_time = 72 * 60;

  // Default increment step (1 )
  static constexpr unsigned int default_increment_time = 1;

  //
  static constexpr unsigned int transit_time = 30;

  //
  static constexpr unsigned int unload_time = 5;

  //
  static constexpr unsigned int min_mining_time = 60;

  //
  static constexpr unsigned int mining_time_range = 4 * 60;

  //
  static constexpr unsigned int INVALID_ID =
      std::numeric_limits<unsigned int>::max();
};

enum class TruckState { mining_trip, station_processing };

enum class TruckEvent { mining_trip_complete, unload_complete };

#endif // CONSTANTS_H
