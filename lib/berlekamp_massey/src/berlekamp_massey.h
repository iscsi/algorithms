#pragma once
#include <tools.h>
#include <lib/number_theory/src/basic_number_theory.h>

inline vector<int32_t> BerlekampMassey(const vector<int32_t>& x, int32_t mod)
{
	//ls: (shortest) relation sequence (after filling zeroes) so far
	//cur: current relation sequence
	vector<int32_t> ls, cur;
	//lf: the position of ls (t')
	//ld: delta of ls (v')
	int32_t lf, ld;
	forn(i, x.size())
	{
		int64_t t = 0;
		//evaluate at position i
		forn(j, cur.size())
		{
			t = (t + x[i - j - 1] * static_cast<int64_t>(cur[j])) % mod;
		}
			
		if ((t - x[i]) % mod == 0) 
			continue; //good so far
		//first non-zero position
		if (!cur.size())
		{
			cur.resize(i + 1);
			lf = i; ld = (t - x[i]) % mod;
			continue;
		}
		//cur=cur-c/ld*(x[i]-t)
		int32_t k = -(x[i] - t)*inverse<int64_t>(ld, mod) % mod;
		vector<int32_t> c(i - lf - 1); //add zeroes in front
		c.push_back(k);
		forn(j, ls.size())
			c.push_back((-ls[j] * static_cast<int64_t>(k))%mod);
		if (c.size() < cur.size()) 
			c.resize(cur.size());
		for (int j = 0; j<int(cur.size()); ++j)
			c[j] = (c[j] + cur[j]) % mod;
		//if cur is better than ls, change ls to cur
		if (i - lf + (int)ls.size() >= (int)cur.size())
			ls = cur, lf = i, ld = (t - x[i]) % mod;
		cur = c;
	}
	for (int i = 0; i<int(cur.size()); ++i)
		cur[i] = (cur[i] % mod + mod) % mod;
	return cur;
}