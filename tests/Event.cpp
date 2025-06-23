#include <Constants.h>
#include <Event.h>

#include <gtest/gtest.h>

TEST(EventTest, GreaterThanTest) {
    Event event0(0, TruckEvent::mining_trip_complete, 0);
    Event event1(1, TruckEvent::mining_trip_complete, 1);

    EXPECT_TRUE(event1 > event0);
    EXPECT_FALSE(event0 > event1);
    EXPECT_FALSE(event0 > event0);
}
