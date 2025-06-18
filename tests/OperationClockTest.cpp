#include <gtest/gtest.h>
#include "OperationClock.h"

// Test 1: Default Constructor Initialization
TEST(OperationClockTest, DefaultInitialization) {
    MiningSimulation::OperationClock clock;
    EXPECT_TRUE(clock.not_expired());  // Should be active at time=0
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
