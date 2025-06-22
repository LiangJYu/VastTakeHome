#include <vector>
#include <Constants.h>
#include <MiningTruck.h>
#include <UnloadStation.h>
#include <gtest/gtest.h>

TEST(UnloadStationTest, DefaultInitialization) {
    // Init default station.
    MiningSimulation::UnloadStation unload_station;

    // Check that all initial values are as expected.
    EXPECT_EQ(unload_station.get_id(), MiningSimulation::Constants::INVALID_ID);
    // Check that queue is empty and there's zero wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 0);
    EXPECT_EQ(unload_station.get_wait_time(), 0);
    // Check that INVALID_ID is current truck.
    EXPECT_EQ(unload_station.get_current_truck_id(), MiningSimulation::Constants::INVALID_ID);
}

TEST(UnloadStationTest, TransitionTesting) {
    // Init default station.
    MiningSimulation::UnloadStation unload_station;

    // Assign truck 0 to station.
    unload_station.assign_truck_get_queue_pos(0);
    // Truck 0 should be truck currently being unloaded.
    EXPECT_EQ(unload_station.get_current_truck_id(), 0);
    // Check that queue is empty and there's zero wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 0);
    EXPECT_EQ(unload_station.get_wait_time(), 0);

    // Assign truck 1 to station.
    unload_station.assign_truck_get_queue_pos(1);
    // Truck 0 should be truck still being unloaded.
    EXPECT_EQ(unload_station.get_current_truck_id(), 0);
    // Queue should have one truck and corresponding wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 1);
    EXPECT_EQ(unload_station.get_wait_time(), MiningSimulation::Constants::unload_time);

    // Assign truck 2 to station.
    unload_station.assign_truck_get_queue_pos(2);
    // Truck 0 should be truck still being unloaded.
    EXPECT_EQ(unload_station.get_current_truck_id(), 0);
    // Queue should have two trucks and double previous wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 2);
    EXPECT_EQ(unload_station.get_wait_time(), 2 * MiningSimulation::Constants::unload_time);

    // Truck 0 should have departed.
    auto id_departing_truck = unload_station.truck_departure();
    EXPECT_EQ(id_departing_truck, 0);
    // Truck 1 should be truck currently being unloaded.
    EXPECT_EQ(unload_station.get_current_truck_id(), 1);
    // Queue should have one truck and corresponding wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 1);
    EXPECT_EQ(unload_station.get_wait_time(), MiningSimulation::Constants::unload_time);

    // Truck 1 should have departed.
    id_departing_truck = unload_station.truck_departure();
    // Truck 2 should be truck currently being unloaded.
    EXPECT_EQ(id_departing_truck, 1);
    EXPECT_EQ(unload_station.get_current_truck_id(), 2);
    // Check that queue is empty and there's zero wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 0);
    EXPECT_EQ(unload_station.get_wait_time(), 0);

    // Truck 2 should have departed.
    id_departing_truck = unload_station.truck_departure();
    EXPECT_EQ(id_departing_truck, 2);
    // Check for invalid since station is completely empty.
    EXPECT_EQ(unload_station.get_current_truck_id(), MiningSimulation::Constants::INVALID_ID);
    // Check that queue is empty and there's zero wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 0);
    EXPECT_EQ(unload_station.get_wait_time(), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
