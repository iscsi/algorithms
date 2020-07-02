#pragma once
#include <rili/Test.h>
#include <rili/test/Main.h>
#include <lib/suffix_array/suffix_array_all.h>

TEST(ShortTest1, SAShortTest)
{
	string s("ababba");
	auto res = suffixArray(s);
	EXPECT_EQ(res,vector<uint32_t>({6,5,0,2,4,1,3}));
	}