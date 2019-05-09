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

void perfTest(uint32_t N, performance::performancePoint& start, performance::performancePoint& end)
{
	vector<uint32_t> v = generateVector<uint32_t>(N, 0, numeric_limits<uint32_t>::max());
	start = performance::now();
	sort(all(v));
	end = performance::now();
}

void perfTest2(uint32_t N, performance::performancePoint& start, performance::performancePoint& end)
{
	start = performance::now();
	vector<uint32_t> w = generateVector<uint32_t>(N, 0, numeric_limits<uint32_t>::max());

	vector<Treap::Node> v;
	const uint32_t ITEM_COUNT = N;
	forn(i, ITEM_COUNT)
		v.emplace_back(Treap::Node(w[i]));

	Treap::Node* t = nullptr;
	forn(i, ITEM_COUNT)
		Treap::insert(t, &v[i]);
	end = performance::now();
}

void perfTest3(uint32_t N, performance::performancePoint& start, performance::performancePoint& end)
{
	vector<uint32_t> w = generateVector<uint32_t>(N, 0, numeric_limits<uint32_t>::max());

	vector<Treap::Node> v;
	const uint32_t ITEM_COUNT = N;
	forn(i, ITEM_COUNT)
		v.emplace_back(Treap::Node(w[i]));

	Treap::Node* t = nullptr;
	forn(i, ITEM_COUNT)
		Treap::insert(t, &v[i]);

	vector<uint32_t> q = generateVector<uint32_t>(100000, 0, numeric_limits<uint32_t>::max());

	start = performance::now();

	forn(i, q.size())
		Treap::getCount(t, q[i]);

	end = performance::now();
}

int main(int argc, char** argv) 
{
	GeometricProgression<uint32_t> gp(100, 2);
	const int numberOfTest = 14;
	vector<pair< uint32_t, vector<double > > > res(numberOfTest);
	vector<pair< uint32_t, double> > rt(numberOfTest);
	vector<double> res2(numberOfTest), res3(numberOfTest), res4(numberOfTest), res5(numberOfTest),res6(numberOfTest), res7(numberOfTest), res8(numberOfTest);

	forn(i, numberOfTest)
	{
		res[i].first = gp.get(i);
		double actsum = 0;
		forn(j, 5)
		{
			double tmp = performance::performanceTest(perfTest2, res[i].first);
			res[i].second.push_back(tmp);
			actsum += tmp;
		}
		//actsum /= 5;
		sort(all(res[i].second));
		actsum = res[i].second[2];
		res2[i] = actsum / (res[i].first * log(res[i].first));
		res3[i] = actsum / (res[i].first);
		res4[i] = actsum / (res[i].first * log(res[i].first) * log(res[i].first));
		res5[i] = actsum / (static_cast<double>(res[i].first) * res[i].first);
		res6[i] = actsum / (log(res[i].first));
		res7[i] = actsum / (log(res[i].first)*log(res[i].first));
		res8[i] = actsum / (sqrt(res[i].first));
		rt[i].first = res[i].first;
		rt[i].second = actsum;
	}

	performance::Complexity co = performance::calculateComplexity(rt);


	getchar();
	return 0;
}
