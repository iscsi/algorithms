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

TEST(FenwickTreeTest, FenwickTreeFastInitTest)
{
	FenwickTree<uint32_t> fw;
	fw.fastInit({ 5, 0, 7, 4, 3, 1, 9 });
	EXPECT_EQ(fw.sum(2), 12);
	EXPECT_EQ(fw.sum(3), 16);
	EXPECT_EQ(fw.sum(6), 29);
	fw.inc(1, 11);
	EXPECT_EQ(fw.sum(6), 40);
}

TEST(FenwickTreeTest, FenwickTreePerformanceInitTest)
{
	FenwickTree<uint64_t> fw;
	vector<uint64_t> v = generateVector<uint64_t>(1000000, 0, 1000000000);
	fw.init(v);
}

TEST(FenwickTreeTest, FenwickTreePerformanceFastInitTest)
{
	FenwickTree<uint64_t> fw;
	vector<uint64_t> v = generateVector<uint64_t>(1000000, 0, 1000000000);
	fw.fastInit(v);
}

TEST(FenwickTreeTest, FenwickTreeInitComparisionTest)
{
	FenwickTree<uint64_t> fw, fw2;
	vector<uint64_t> v = generateVector<uint64_t>(100000, 0, 1000000000);
	fw.init(v);
	fw2.fastInit(v);
	EXPECT_EQ(fw.data, fw2.data);
}
