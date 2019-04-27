#pragma once
#include <rili/Test.h>
#include <rili/test/Main.h>

#include <lib/segment_tree/segment_tree_all.h>

TEST(SegmentTreeTest, SegmentTreeSmallBuildTest)
{
	SegmentTree<uint32_t> st({ 5,0,7,4,3,1,9 });
	EXPECT_EQ(st.query(1,2), 0);
	EXPECT_EQ(st.query(3, 6),1);
	EXPECT_EQ(st.query(6, 7), 9);
}
