#pragma once
#include <rili/Test.h>
#include <rili/test/Main.h>
#include <lib/segment_tree/segment_tree_all.h>

TEST(SegmentTreeSimpleTest, SegmentTreeSimpleSmallBuildTest)
{
	SegmentTreeSimple<uint32_t> st({ 5, 0, 7, 4, 3, 1, 9});
	EXPECT_EQ(st.query(1, 2), 0);
	EXPECT_EQ(st.query(3, 6), 1);
	EXPECT_EQ(st.query(6, 7), 9);
}

TEST(SegmentTreeLazyTest, SegmentTreeLazySmallBuildTest)
{
	SegmentTreeLazy<uint32_t> stl({ 5, 0, 7, 4, 3, 1, 9});
	EXPECT_EQ(stl.query(1, 2), 0);
	EXPECT_EQ(stl.query(3, 6), 1);
	EXPECT_EQ(stl.query(6, 7), 9);
}


TEST(SegmentTreeLazyTest, SegmentTreeLazySmallUpdateTest)
{
	SegmentTreeLazy<uint32_t> stl({ 5, 0, 7, 4, 3, 1, 9});
	EXPECT_EQ(stl.query(0, 7), 0);
	stl.modify(0, 3, 2);
	EXPECT_EQ(stl.query(0, 1), 7);
	EXPECT_EQ(stl.query(1, 2), 2);
	EXPECT_EQ(stl.query(2, 3), 9);
	EXPECT_EQ(stl.query(3, 4), 4);
	EXPECT_EQ(stl.query(0, 4), 2);
	EXPECT_EQ(stl.query(0, 7), 1);
}
