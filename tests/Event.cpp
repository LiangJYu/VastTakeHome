#include <Constants.h>
#include <Event.h>

#include <gtest/gtest.h>

TEST(EventTest, DefaultInitialization) {

    Event event(0, TruckEvent::mine_arrival, 1);

    EXPECT_EQ(event.get_id(), 0);
    EXPECT_EQ(event.get_completion_event(), TruckEvent::mine_arrival);
    EXPECT_EQ(event.get_t_completion(), 1);
}

TEST(EventTest, GreaterThanTest) {
    Event event0(0, TruckEvent::mine_arrival, 0);
    Event event1(1, TruckEvent::mine_arrival, 1);

    EXPECT_TRUE(event1 > event0);
    EXPECT_FALSE(event0 > event1);
    EXPECT_FALSE(event0 > event0);
}
