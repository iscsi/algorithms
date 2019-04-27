#pragma once
#include <rili/Test.h>
#include <rili/test/Main.h>

#include <lib/searching/searching_all.h>

TEST(BinarySearchTest, BinarySearchSmallTest)
{
	EXPECT_EQ(bin_search({ 1,4,5,5,6,8,9,11 }, 0), -1);
	EXPECT_EQ(bin_search({ 1,4,5,5,6,8,9,11 }, 5), 3);
	EXPECT_EQ(bin_search({ 1,4,5,5,6,8,9,11 }, 13), 7);
}
