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

int main(int argc, char** argv) 
{
/*#ifdef HOME
	if(IsDebuggerPresent())
	{
		freopen("../in.txt", "rb", stdin);
		freopen("../out.txt", "wb", stdout);
	}
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;
#endif*/

	return rili::test::main(argc, argv);

	rili::test::runner::run([](std::string const& /*fixture*/, std::string const& scenario) {
		if (std::regex_match(scenario, std::regex("(SKIP_)(.*)"))) {
			return rili::test::runner::FilteringResult::Skip;
		}
		else if (std::regex_match(scenario, std::regex("(DISABLE_)(.*)"))) {
			return rili::test::runner::FilteringResult::Disable;
		}
		else {
			return rili::test::runner::FilteringResult::Run;
		}
	});
	getchar();
	return 0;
	return 0;
}
