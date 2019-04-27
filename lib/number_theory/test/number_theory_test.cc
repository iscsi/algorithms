#include <rili/Test.h>
#include <rili/test/Main.h>

#include <lib/number_theory/number_theory.h>

// This can be moved to separate files
TEST(GCDTest, GCDTestPrimes)
{
	EXPECT_EQ(gcd(7, 12), 1);
}

int main(int argc, char* argv[])
{
	return rili::test::main(argc, argv);
}