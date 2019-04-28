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

TEST(TernarySearchTest, TernarySearchDoubles)
{
	EXPECT_NEARLY(ternary_search<long double>(sinl,-0.2,0.4), 0.0, 1e-10);
}


TEST(TernarySearchTest, TernarySearchIntegralEvenResult)
{
	EXPECT_EQ(ternary_searchInt<uint64_t>([](int64_t A) {return static_cast<uint64_t>(std::abs(A - 12345334) + 5); }, -1000000000000000L, 1000000000000000L), 12345334);
}

TEST(TernarySearchTest, TernarySearchIntegralOddResult)
{
	EXPECT_EQ(ternary_searchInt<uint64_t>([](int64_t A) {return static_cast<uint64_t>(std::abs(A - 12345335) + 5); }, -1000000000000000L, 1000000000000000L), 12345335);
}

TEST(TernarySearchTest, TernarySearchIntegralIntervalBegin)
{
	EXPECT_EQ(ternary_searchInt<uint64_t>([](int64_t A) {return static_cast<uint64_t>(std::abs(A + 1000000000000000L) + 5); }, -1000000000000000L, 1000000000000000L), -1000000000000000L);
}

TEST(TernarySearchTest, TernarySearchIntegralIntervalEnd)
{
	EXPECT_EQ(ternary_searchInt<uint64_t>([](int64_t A) {return static_cast<uint64_t>(std::abs(A - 1000000000000000L) + 5); }, -1000000000000000L, 1000000000000000L), 1000000000000000L);
}


