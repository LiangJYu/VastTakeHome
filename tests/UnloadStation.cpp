#include <vector>
#include <Constants.h>
#include <MiningTruck.h>
#include <UnloadStation.h>
#include <gtest/gtest.h>

TEST(UnloadStationTest, DefaultInitialization) {
    // Init default station.
    UnloadStation unload_station;

    // Check that all initial values are as expected.
    EXPECT_EQ(unload_station.get_id(), Constants::INVALID_ID);
    // Check that queue is empty and there's zero wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 0);
    EXPECT_EQ(unload_station.get_wait_time(), 0);
    // Check that INVALID_ID is current truck.
    EXPECT_EQ(unload_station.get_current_truck_id(), Constants::INVALID_ID);
}

TEST(UnloadStationTest, TransitionTesting) {
    // Init default station.
    UnloadStation unload_station;

    // Test station events.
    unsigned int t0 = 0;
    unsigned int id0 = 0;

    unsigned int t1 = 1;
    unsigned int id1 = 1;

    unsigned int t2 = 2;
    unsigned int id2 = 2;

    // Assign truck 0 to station.
    unload_station.assign_truck_get_queue_pos(id0, t0);
    // Truck 0 should be truck currently being unloaded.
    EXPECT_EQ(unload_station.get_current_truck_id(), t0);
    // Check that queue is empty and there's zero wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 0);
    EXPECT_EQ(unload_station.get_wait_time(), 0);

    // Assign truck 1 to station.
    unload_station.assign_truck_get_queue_pos(id1, t1);
    // Truck 0 should be truck still being unloaded.
    EXPECT_EQ(unload_station.get_current_truck_id(), id0);
    // Queue should have one truck and corresponding wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 1);
    EXPECT_EQ(unload_station.get_wait_time(), Constants::unload_time);

    // Assign truck 2 to station.
    unload_station.assign_truck_get_queue_pos(id2, t2);
    // Truck 0 should be truck still being unloaded.
    EXPECT_EQ(unload_station.get_current_truck_id(), 0);
    // Queue should have two trucks and double previous wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 2);
    EXPECT_EQ(unload_station.get_wait_time(), 2 * Constants::unload_time);

    // Truck 0 should have departed.
    auto id_departing_truck = unload_station.truck_departure(t2 + 1);
    EXPECT_EQ(id_departing_truck, id0);
    // Truck 1 should be truck currently being unloaded.
    EXPECT_EQ(unload_station.get_current_truck_id(), id1);
    // Queue should have one truck and corresponding wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 1);
    EXPECT_EQ(unload_station.get_wait_time(), Constants::unload_time);

    // Truck 1 should have departed.
    id_departing_truck = unload_station.truck_departure(t2 + 2);
    // Truck 2 should be truck currently being unloaded.
    EXPECT_EQ(id_departing_truck, id1);
    EXPECT_EQ(unload_station.get_current_truck_id(), id2);
    // Check that queue is empty and there's zero wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 0);
    EXPECT_EQ(unload_station.get_wait_time(), 0);

    // Truck 2 should have departed.
    id_departing_truck = unload_station.truck_departure(t2 + 3);
    EXPECT_EQ(id_departing_truck, id2);
    // Check for invalid since station is completely empty.
    EXPECT_EQ(unload_station.get_current_truck_id(), Constants::INVALID_ID);
    // Check that queue is empty and there's zero wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 0);
    EXPECT_EQ(unload_station.get_wait_time(), 0);

    // Unload a completely empty station.
    id_departing_truck = unload_station.truck_departure(t2 + 4);
    EXPECT_EQ(id_departing_truck, Constants::INVALID_ID);
    // Check that queue is empty and there's zero wait time.
    EXPECT_EQ(unload_station.get_queue_length(), 0);
    EXPECT_EQ(unload_station.get_wait_time(), 0);

    // Validate stats.
    auto stats = unload_station.get_stats();
    EXPECT_EQ(stats.n_unloads, 3);
    EXPECT_EQ(stats.queue_len_vs_time.size(), 5);

    std::vector<unsigned int> t_change_expected({0, 1, 2, 3, 4});
    std::vector<unsigned int> q_length_expected({0, 1, 2, 1, 0});
    for (int i = 0; i < 5; ++i) {
        auto len = std::get<0>(stats.queue_len_vs_time[i]);
        EXPECT_EQ(len, q_length_expected[i]);
        auto t = std::get<1>(stats.queue_len_vs_time[i]);
        EXPECT_EQ(t, t_change_expected[i]);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
