#pragma once
#include <rili/Test.h>
#include <rili/test/Main.h>
#include <lib/treap/treap_all.h>

TEST(TreapTest, TreapSmallTest)
{
	vector<Treap::Node> v({ 5,3,11,22,2 });

	Treap::Node* t = nullptr;

	forn(i, 5)
		Treap::insert(t, &v[i]);
	
	EXPECT_EQ(Treap::getSize(t), 5);
}


//compare treap vs set performance
TEST(TreapTest, TreapKeyTestVsSetTreapTest)
{
	vector<Treap::Node> v;
	const uint32_t ITEM_COUNT = 200000;
	forn(i, ITEM_COUNT)
		v.emplace_back(Treap::Node(i));

	Treap::Node* t = nullptr;
	forn(i, ITEM_COUNT)
		Treap::insert(t, &v[i]);
		
	forn(i, ITEM_COUNT)
		ASSERT_EQ(Treap::getCount(t, i), 1);
}


TEST(TreapTest, TreapKeyTestVsSetSetTest)
{
	const uint32_t ITEM_COUNT = 200000;

	set<uint32_t> s;
	forn(i, ITEM_COUNT)
		s.insert(i);
		
	forn(i, ITEM_COUNT)
		ASSERT_EQ(s.count(i), 1);
}



//compare treap vs multiset performance
TEST(TreapTest, TreapKeyTestVsMSetTreapTest)
{
	vector<Treap::Node> v;
	const uint32_t ITEM_COUNT = 100000;
	forn(r,3)
		forn(i, ITEM_COUNT)
			v.emplace_back(Treap::Node(i));

	Treap::Node* t = nullptr;
	forn(i, v.size())
		Treap::insert(t, &v[i]);

	forn(i, ITEM_COUNT)
		ASSERT_EQ(Treap::getCount(t, i), 3);
}


TEST(TreapTest, TreapKeyTestVsMSetMSetTest)
{
	const uint32_t ITEM_COUNT = 100000;

	multiset<uint32_t> ms;
	forn(r, 3)
		forn(i, ITEM_COUNT)
		ms.insert(i);

	forn(i, ITEM_COUNT)
		ASSERT_EQ(ms.count(i), 3);
}
/*
TEST(TreapPoolTest, TreapPoolSmallTest)
{
	TreapNode::mPool.init(1000);

	vector<uint32_t> w({ 5,3,11,22,2 });
	uint32_t r = 0;

	forn(i, 5)
	{
		uint32_t id = TreapNode::mPool.get();
		TreapNode::mPool.mData[id].value = w[i];
		TreapNode::mPool.mData[id].insert(r, id);
	}

	EXPECT_EQ(TreapNode::mPool.mData[r].getSize(), 5);
}*/

