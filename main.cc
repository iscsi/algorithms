#include <my_template.h>
#include <tools.h>
#include <lib/lib.h>
#include <rili/Test.h>
#include <rili/test/Main.h>


#include <exception>

#ifdef NDEBUG
inline void examples_assert(bool exprResult) {
	if (!exprResult) {
		std::terminate();
	}
}
#define EXAMPLES_ASSERT(X) examples_assert(X)
#else
#define EXAMPLES_ASSERT(X) assert(X)
#endif 
class ExpectSuccess : public rili::test::TestBaseFixture {
public:
	void after() override { EXAMPLES_ASSERT(!rili::test::EventHandler::getInstance().currentTestFailed()); }
};

class ExpectFailure : public rili::test::TestBaseFixture {
public:
	void after() override { EXAMPLES_ASSERT(rili::test::EventHandler::getInstance().currentTestFailed()); }
};
/*
TEST_F(ExpectFailure, AddFailure) {
	ADD_FAILURE("some message");
	ADD_FAILURE();
}*/


TEST(EulerTotient, TestEulerTotient)
{
	int tmp = eulerTotient(11);
	EXPECT_EQ(tmp, 12);
}

TEST_F(ExpectSuccess, NumberOfTestGreaterThanZero) { EXPECT_GT(rili::test::TestStorage::getInstance().size(), 0u); }

void perfTest(uint32_t N, std::chrono::time_point<std::chrono::steady_clock>& start, std::chrono::time_point<std::chrono::steady_clock>& end)
{
	vector<uint32_t> v = generateVector<uint32_t>(N, 0, numeric_limits<uint32_t>::max());
	start = std::chrono::steady_clock::now();
	sort(all(v));
	end = std::chrono::steady_clock::now();
}

int main(int argc, char** argv) 
{
	GeometricProgression<uint32_t> gp(10, 10);
	vector<double > res(6);

	
	forn(i, 6)
	{
		forn(j, 5)
			res[i] += performance::performanceTest(perfTest, gp.get(i));
		res[i] /= 5;
	}
	getchar();
	return 0;
}
