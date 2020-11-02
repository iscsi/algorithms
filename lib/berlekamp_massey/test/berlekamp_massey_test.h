#pragma once
#include <rili/Test.h>
#include <rili/test/Main.h>
#include <lib/berlekamp_massey/berlekamp_massey_all.h>

TEST(BMTest, BM1)
{
	int32_t mod = 1e9 + 7;
	uint32_t K = getRandom<uint32_t>(5, 10);
	vector<int32_t> w(100000);
	vector<int32_t> p(K);
	forn(i, K)
	{
		p[i] = getRandom(5, 100000);
		w[i] = getRandom(5, 100000);
	}
	fore(i, K, w.size() - 1)
	{
		forn(j, K)
		{
			w[i] = (w[i] + static_cast<int64_t>(p[j])*w[i-1-j]) % mod;
		}
	}

	vector<int32_t> bmin = w;
	bmin.resize(2 * K);
	vector<int32_t> bmRes = BerlekampMassey(bmin, mod);
	bmin.resize(w.size());
	fore(i, 2*K, w.size() - 1)
	{
		forn(j, K)
		{
			bmin[i] = (bmin[i] + static_cast<int64_t>(bmRes[j]) * bmin[i - 1 - j]) % mod;
		}
	}
	EXPECT_EQ(bmin, w);
}
