#include <OperationClock.h>

#include <gtest/gtest.h>

TEST(OperationClockTest, DefaultInitialization) {
    MiningSimulation::OperationClock clock;

    // Should init current time to 0.
    EXPECT_EQ(clock.get_current_time(), 0);

    // Should be not expired at time=0.
    EXPECT_TRUE(clock.not_expired());
}

TEST(OperationClockTest, Prefix) {
    MiningSimulation::OperationClock clock;

    // Compute expected value.
    auto t_expected = clock.get_current_time() + clock.get_t_increment();

    // Get time time after prefix.
    ++clock;
    auto t_prefix = clock.get_current_time();

    EXPECT_EQ(t_expected, t_prefix);
}

TEST(OperationClockTest, Postfix) {
    MiningSimulation::OperationClock clock;

    // Get expected current time.
    auto t_expected = clock.get_current_time();

    // Get original time before postfix.
    auto clock_postfix = clock++;
    auto t_postfix = clock_postfix.get_current_time();

    EXPECT_EQ(t_expected, t_postfix);
}

// Test 2: Expiration Conditions
TEST(OperationClockTest, ExpirationConditions) {
    MiningSimulation::OperationClock clock;

    // Check initialized time has not expired.
    EXPECT_TRUE(clock.not_expired());  // Should be active at time=0

    while (clock.not_expired()) {
        ++clock;
    }

    // Check final time is end time and clock has expired.
    EXPECT_FALSE(clock.not_expired());
    EXPECT_EQ(clock.get_current_time(), clock.get_end_time());

    // Check increment final time and check it does not exceed end time and clock remains expired.
    ++clock;
    EXPECT_FALSE(clock.not_expired());
    EXPECT_EQ(clock.get_current_time(), clock.get_end_time());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
