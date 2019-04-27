#pragma once
#include <rili/Test.h>
#include <rili/test/Main.h>
#include <lib/number_theory/number_theory.h>

TEST(GCDTest, GCDTestPrimes)
{
	EXPECT_EQ(gcd(7, 12), 1);
}
