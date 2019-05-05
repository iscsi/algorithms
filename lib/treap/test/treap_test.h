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


TEST(TreapTest, TreapKeyTestVsSetTreapTest)
{
	vector<Treap::Node> v;
	const uint32_t ITEM_COUNT = 200000;
	forn(i, ITEM_COUNT)
		v.emplace_back(Treap::Node(i));

	Treap::Node* t = nullptr;
	forn(i, ITEM_COUNT)
	{
		Treap::insert(t, &v[i]);
	}
	
	forn(i, ITEM_COUNT)
	{
		ASSERT_EQ(Treap::getCount(t,i), 1);
	}
}


TEST(TreapTest, TreapKeyTestVsSetSetTest)
{
	const uint32_t ITEM_COUNT = 200000;
	
	set<uint32_t> s;
	forn(i, ITEM_COUNT)
	{
		s.insert(i);
	}

	forn(i, ITEM_COUNT)
	{
		ASSERT_EQ(s.count(i), 1);
	}
}
