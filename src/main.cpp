#include "Event.h"
#include "MiningTruck.h"
#include "OperationClock.h"
#include "UnloadStation.h"
#include <format>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>

auto main(int argc, char *argv[]) -> int {
  if (argc != 3) {
    throw std::invalid_argument(
        std::format("{} argument(s) given, 2 expected\n", argc - 1));
  }

  // TODO add input validation
  unsigned int n_trucks = std::stoul(argv[1]);

  unsigned int n_stations = std::stoul(argv[2]);

  std::cout << std::format("n_trucks {}, n_stations {} \n", n_trucks,
                           n_stations);

  // Initialize user specified number of trucks.
  std::vector<MiningTruck> trucks;
  std::priority_queue<Event, std::vector<Event>, std::greater<Event>> events;
  for (int i = 0; i < n_trucks; ++i) {
    trucks.push_back(MiningTruck(i));

    // Create initial events per trucks and enter into priority queue.
    events.push(Event(i, trucks[i].get_completion_event(), 0));
  }

  // Initialize user specified number of stations.
  std::vector<UnloadStation> stations;
  for (int i = 0; i < n_stations; ++i) {
    stations.push_back(UnloadStation(i));
  }

  // Initialize clock and run while clock not expired.
  OperationClock op_clock;
  while (op_clock.not_expired()) {
    // Get event with smallest t_completion.
    Event current_event = events.top();
    events.pop();

    // Get current time and update clock.
    const auto t_duration =
        current_event.get_t_completion() - op_clock.get_current_time();
    op_clock.add_time(t_duration);
    const auto t_now = op_clock.get_current_time();

    // Get truck from event.
    auto &truck = trucks[current_event.get_truck_id()];

    // Default to no waiting at station.
    unsigned int queue_pos = 0;

    // Initialize chosen station to INVALID_ID. To be updated if/when station
    // with shortest wait time found.
    unsigned int id_chosen_station = Constants::INVALID_ID;

    // When mining trip complete, determine station with shortest wait time.
    if (current_event.get_type() == TruckEvent::mining_trip_complete) {
      // Init to max unsigned int so something smaller will be found.
      auto t_min_wait = std::numeric_limits<unsigned int>::max();

      // nullptr will be replaced by pointer to station with shortest wait.
      UnloadStation *chosen_station = nullptr;

      // Iterate through all stations. Compare and update as needed.
      for (auto &station : stations) {
        if (t_min_wait > station.get_wait_time()) {
          t_min_wait = station.get_wait_time();
          chosen_station = &station;
          id_chosen_station = chosen_station->get_id();
        }
      }

      // Assign truck to chosen station and get queue position.
      queue_pos =
          chosen_station->assign_truck_get_queue_pos(truck.get_id(), t_now);
    }

    if (current_event.get_type() == TruckEvent::processing_complete) {
      // XXX check if event truck_id == return from dispatch_truck?
      stations[current_event.get_station_id()].dispatch_truck(t_now);
    }

    // Advance state and push its event into event priority_queue.
    events.push(
        truck.advance_state_get_event(t_now, queue_pos, id_chosen_station));
  }
  return 0;
}
