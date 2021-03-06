#pragma once
#include <rili/Test.h>
#include <rili/test/Main.h>
#include <lib/segment_tree/segment_tree_all.h>

TEST(SegmentTreeBUSimpleTest, SegmentTreeBUSimpleSmallBuildTest)
{
	SegmentTreeBUSimple<uint32_t> st({ 5, 0, 7, 4, 3, 1, 9 });
	EXPECT_EQ(st.query(1, 2), 0);
	EXPECT_EQ(st.query(3, 6), 1);
	EXPECT_EQ(st.query(6, 7), 9);
}

TEST(SegmentTreeBULazyTest, SegmentTreeBULazySmallBuildTest)
{
	SegmentTreeBULazy<uint32_t> stl({ 5, 0, 7, 4, 3, 1, 9 });
	EXPECT_EQ(stl.query(1, 2), 0);
	EXPECT_EQ(stl.query(3, 6), 1);
	EXPECT_EQ(stl.query(6, 7), 9);
}


TEST(SegmentTreeBULazyTest, SegmentTreeBULazySmallUpdateTest)
{
	SegmentTreeBULazy<uint32_t> stl({ 5, 0, 7, 4, 3, 1, 9 });
	EXPECT_EQ(stl.query(0, 7), 0);
	stl.modify(0, 3, 2);
	EXPECT_EQ(stl.query(0, 1), 7);
	EXPECT_EQ(stl.query(1, 2), 2);
	EXPECT_EQ(stl.query(2, 3), 9);
	EXPECT_EQ(stl.query(3, 4), 4);
	EXPECT_EQ(stl.query(0, 4), 2);
	EXPECT_EQ(stl.query(0, 7), 1);
}

TEST(SegmentTreeSimpleTest, SegmentTreeSimpleSmallBuildTest)
{
	SegmentTreeLazy<uint32_t> st({ 5, 0, 7, 4, 3, 1, 9 });
	EXPECT_EQ(st.query(1, 2), 0);
	EXPECT_EQ(st.query(3, 6), 1);
	EXPECT_EQ(st.query(6, 7), 9);
}

TEST(SegmentTreeLazyTest, SegmentTreeLazySmallUpdateTest)
{
	SegmentTreeBULazy<uint32_t> stl({ 5, 0, 7, 4, 3, 1, 9 });
	EXPECT_EQ(stl.query(0, 7), 0);
	stl.modify(0, 3, 2);
	EXPECT_EQ(stl.query(0, 1), 7);
	EXPECT_EQ(stl.query(1, 2), 2);
	EXPECT_EQ(stl.query(2, 3), 9);
	EXPECT_EQ(stl.query(3, 4), 4);
	EXPECT_EQ(stl.query(0, 4), 2);
	EXPECT_EQ(stl.query(0, 7), 1);
}

TEST(SegmentTreeCrossValidateTest, SegmentTreeCrossValidateTestSmall)
{
	int segmentTreeS = getRandom<uint32_t>(3, 50000);
	auto segmentTreeData = generateVector<uint32_t>(segmentTreeS, 2, 10000);

	SegmentTreeBULazy<uint32_t> sbul(segmentTreeData);
	SegmentTreeLazy<uint32_t> sl(segmentTreeData);

	forn(i, 1000)
	{
		uint32_t l = getRandom<uint32_t>(0, segmentTreeS - 1);
		uint32_t r = getRandom<uint32_t>(l + 1, segmentTreeS);
		if (i & 1)
		{
			EXPECT_EQ(sbul.query(l, r), sl.query(l, r));
		}
		else
		{
			uint32_t val = getRandom<uint32_t>(0, 10000);
			sbul.modify(l, r, val);
			sl.update(l, r, val);
		}
	}
}

TEST(SegmentTreeQueryComplexityTest, SegmentTreeQueryComplexityTest)
{
	GeometricProgression<uint32_t> gp(100, 2);
	const int numberOfTest = 14;
	
	vector<pair< uint32_t, double> > rt(numberOfTest);
	
	forn(i, numberOfTest)
	{
		uint32_t segmentTreeS = gp.get(i);
		auto segmentTreeData = generateVector<uint32_t>(segmentTreeS, 2, 10000);

		SegmentTreeLazy<uint32_t> sl(segmentTreeData);

		auto queryTest = [&sl, &segmentTreeS]()
		{
			forn(i, 5000)
			{
				uint32_t l = getRandom<uint32_t>(0, segmentTreeS - 1);
				uint32_t r = getRandom<uint32_t>(l + 1, segmentTreeS);
				sl.query(l, r);
			}
		};

		double tmp = performance::performanceTest(queryTest);
		rt[i] = { segmentTreeS, tmp };
	}

	EXPECT_EQ(performance::Complexity::Logarithmic ,performance::calculateComplexity(rt));
}


TEST(SegmentTreeUpdateComplexityTest, SegmentTreeUpdateComplexityTest)
{
	GeometricProgression<uint32_t> gp(100, 2);
	const int numberOfTest = 14;

	vector<pair< uint32_t, double> > rt(numberOfTest);

	forn(i, numberOfTest)
	{
		uint32_t segmentTreeS = gp.get(i);
		auto segmentTreeData = generateVector<uint32_t>(segmentTreeS, 2, 10000);

		SegmentTreeLazy<uint32_t> sl(segmentTreeData);

		auto queryTest = [&sl, &segmentTreeS]()
		{
			forn(i, 50000)
			{
				uint32_t l = getRandom<uint32_t>(0, segmentTreeS - 1);
				uint32_t r = getRandom<uint32_t>(l + 1, segmentTreeS);
				uint32_t val = getRandom<uint32_t>(l + 1, segmentTreeS);
				sl.update(l, r, val);
			}
		};

		double tmp = performance::performanceTest(queryTest);
		rt[i] = { segmentTreeS, tmp };
	}

	EXPECT_EQ(performance::Complexity::Logarithmic, performance::calculateComplexity(rt));
}

TEST(SegmentTreeBUQueryComplexityTest, SegmentTreeBUQueryComplexityTest)
{
	GeometricProgression<uint32_t> gp(100, 2);
	const int numberOfTest = 14;

	vector<pair< uint32_t, double> > rt(numberOfTest);

	forn(i, numberOfTest)
	{
		uint32_t segmentTreeS = gp.get(i);
		auto segmentTreeData = generateVector<uint32_t>(segmentTreeS, 2, 10000);

		SegmentTreeBULazy<uint32_t> sl(segmentTreeData);

		auto queryTest = [&sl, &segmentTreeS]()
		{
			forn(i, 5000)
			{
				uint32_t l = getRandom<uint32_t>(0, segmentTreeS - 1);
				uint32_t r = getRandom<uint32_t>(l + 1, segmentTreeS);
				sl.query(l, r);
			}
		};

		double tmp = performance::performanceTest(queryTest);
		rt[i] = { segmentTreeS, tmp };
	}

	EXPECT_EQ(performance::Complexity::Logarithmic, performance::calculateComplexity(rt));
}


TEST(SegmentTreeBUModifyComplexityTest, SegmentTreeBUModifyComplexityTest)
{
	GeometricProgression<uint32_t> gp(100, 2);
	const int numberOfTest = 14;

	vector<pair< uint32_t, double> > rt(numberOfTest);

	forn(i, numberOfTest)
	{
		uint32_t segmentTreeS = gp.get(i);
		auto segmentTreeData = generateVector<uint32_t>(segmentTreeS, 2, 10000);

		SegmentTreeBULazy<uint32_t> sl(segmentTreeData);

		auto queryTest = [&sl, &segmentTreeS]()
		{
			forn(i, 50000)
			{
				uint32_t l = getRandom<uint32_t>(0, segmentTreeS - 1);
				uint32_t r = getRandom<uint32_t>(l + 1, segmentTreeS);
				uint32_t val = getRandom<uint32_t>(l + 1, segmentTreeS);
				sl.modify(l, r, val);
			}
		};

		double tmp = performance::performanceTest(queryTest);
		rt[i] = { segmentTreeS, tmp };
	}

	EXPECT_EQ(performance::Complexity::Logarithmic, performance::calculateComplexity(rt));
}
