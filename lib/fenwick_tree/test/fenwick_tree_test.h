#pragma once
#include <rili/Test.h>
#include <rili/test/Main.h>
#include <lib/fenwick_tree/fenwick_tree_all.h>

TEST(FenwickTreeTest, FenwickTreeTest)
{
	FenwickTree<uint32_t> fw;
	fw.init({ 5, 0, 7, 4, 3, 1, 9 });
	EXPECT_EQ(fw.sum(2), 12);
	EXPECT_EQ(fw.sum(3), 16);
	EXPECT_EQ(fw.sum(6), 29);
	fw.inc(1,11);
	EXPECT_EQ(fw.sum(6), 40);
}
