#pragma once
#include <rili/Test.h>
#include <rili/test/Main.h>
#include <lib/scc/scc_all.h>


TEST(SAT2Test, SAT2Small)
{
	vector<CLAUSE> cnf = {
		{{true,1},{false,0}},
		{{false,0},{false,1}},
		{{true,0},{true,2}},
		{{false,1},{false,2}},
		{{true,0},{true,3}},
	};

	SAT2 s2;
	vector<bool> ass = s2.Calculate(4, cnf);
	EXPECT_EQ(ass.empty(), false);
	EXPECT_EQ(all_of(all(cnf), [&ass](CLAUSE cl) {return cl.calc(ass); }), true);
}