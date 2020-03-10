#include <iostream>

#include "gtest/gtest.h"
#include "p2p/websocket/client.h"

TEST(sample_test_case, sample_test)
{
    P2P::P2PWSClient client("");
    EXPECT_EQ(1, 1);
}