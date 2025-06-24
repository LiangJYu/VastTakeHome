#include <MiningTruck.h>
#include <gtest/gtest.h>
#include <vector>

// Convenience structure containging expected transition results.
struct ExpectedTransition {
  TruckState truck_state;
  unsigned int t_state_start;
  TruckEvent completion_event;
  unsigned int t_completion;
};

TEST(MiningTruckTest, DefaultInitialization) {
  MiningTruck truck(0);

  EXPECT_EQ(truck.get_id_assigned_station(), Constants::INVALID_ID);

  // Should init current time to 0.
  EXPECT_EQ(truck.get_state(), TruckState::mining_trip);

  EXPECT_EQ(truck.get_t_state_start(), 0);

  EXPECT_EQ(truck.get_completion_event(), TruckEvent::mining_trip_complete);

  const auto t_completion{truck.get_t_completion()};
  const auto min_mining_trip_time = 2 * Constants::transit_time + Constants::min_mining_time;
  EXPECT_GE(t_completion, min_mining_trip_time);

  const auto max_mining_time = min_mining_trip_time + Constants::mining_time_range;
  EXPECT_LE(t_completion, max_mining_time);
}

TEST(MiningTruckTest, TransitionTesting) {
  MiningTruck truck(0);

  const auto t_completion{truck.get_t_completion()};

  std::vector<ExpectedTransition> transitions = {
      // initial state of mining
      ExpectedTransition(TruckState::mining_trip, 0,
                         TruckEvent::mining_trip_complete, t_completion),
      // transit-to-unload to unloading
      ExpectedTransition(TruckState::station_processing, t_completion,
                         TruckEvent::unload_complete,
                         t_completion + Constants::unload_time)};

  for (auto tran : transitions) {
    // Ensure that truck state matches expectation at start of state
    EXPECT_EQ(truck.get_state(), tran.truck_state);

    EXPECT_EQ(truck.get_t_state_start(), tran.t_state_start);

    EXPECT_EQ(truck.get_completion_event(), tran.completion_event);

    EXPECT_EQ(truck.get_t_completion(), tran.t_completion);

    // Advance truck state to just before state change and ensure no change
    auto t_just_before_advance = truck.get_t_completion() - 1;
    truck.advance_state_get_event(t_just_before_advance);

    EXPECT_EQ(truck.get_state(), tran.truck_state);

    EXPECT_EQ(truck.get_t_state_start(), tran.t_state_start);

    EXPECT_EQ(truck.get_completion_event(), tran.completion_event);

    EXPECT_EQ(truck.get_t_completion(), tran.t_completion);

    // Advance truck to next state
    truck.advance_state_get_event(truck.get_t_completion());
  }

  // Test computed statistics.
  const auto stats = truck.get_stats();
  EXPECT_EQ(stats.t_transit, 2 * Constants::transit_time);
  EXPECT_EQ(stats.t_mining, t_completion - 2 * Constants::transit_time);
  EXPECT_EQ(stats.t_in_queue, 0);
  EXPECT_EQ(stats.t_unloading, Constants::unload_time);
  EXPECT_EQ(stats.n_trips, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
