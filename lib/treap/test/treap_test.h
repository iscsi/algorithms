#pragma once
#include <rili/Test.h>
#include <rili/test/Main.h>
#include <lib/treap/treap_all.h>

TEST(TreapTest, TreapSmallTest)
{
	Treap::Node* nt = new Treap::Node(5);

	vector<Treap::Node> v({ 5,3,11,22,2 });

	Treap::Node* t = nullptr;

	forn(i, 5)
		Treap::insert(t, &v[i]);
	
	EXPECT_EQ(Treap::getSize(t), 5);
	
}

