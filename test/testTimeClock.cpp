/**
*
* The Black Codex Library: Chapter: C++ Tools
*
* https://github.com/tbc-beren/BCppTools
*
* Mozilla Public License Version 2.0
* https://github.com/tbc-beren/BCppTools/blob/master/LICENSE
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* https://mozilla.org/MPL/2.0/.
*
*/
#include <bcpptools/time/bcclock.hpp>

#include <gtest/gtest.h>

#include <string>
#include <vector>

TEST(TimeClock, BCClock) {
    using namespace bcpptools;

    // Expect current clock is system clock.
    // Does not support wait
    auto now = BCClock::now();
    EXPECT_NE(0, now);
    EXPECT_FALSE(BCClock::advance(1));
}
TEST(TimeClock, BCClockFFw) {
    using namespace bcpptools;

    // Expect current clock is system clock.
    // Does not support wait
    auto now = BCClock::now();
    EXPECT_NE(0, now);
    EXPECT_FALSE(BCClock::advance(1));

    BCClockFFwScoped ffwClock;
    EXPECT_EQ(0, BCClock::now());
    EXPECT_TRUE(BCClock::advance(100));
    EXPECT_EQ(100, BCClock::now());

    EXPECT_EQ(0, BCClock::nowAsSeconds());
    BCClock::advance(1000);
    EXPECT_EQ(1, BCClock::nowAsSeconds());
}
