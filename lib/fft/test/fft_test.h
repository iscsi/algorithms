#pragma once
#include <rili/Test.h>
#include <rili/test/Main.h>
#include <lib/fft/fft_all.h>

TEST(NTTTest, NTTTestMultiplication)
{
	uint64_t a = 0xabcd6789, b = 0x6789abcd;
	auto func = [](uint64_t a) -> vector<uint32_t>
	{
		vector<uint32_t> res;
		while (a)
		{
			res.push_back(a & 1);
			a >>= 1;
		}
		res.resize(64);
		return res;
	};
	vector<uint32_t> va = func(a), vb = func(b);
	NTT<uint32_t> ntt(7);
	va = ntt.transform(va, false);
	vb = ntt.transform(vb, false);
	forn(i, va.size())
		va[i] = (va[i] * vb[i]) % ntt.mod;
	va = ntt.transform(va, true);
	uint32_t rem = 0;
	uint64_t res = 0;
	forn(i, 64)
	{
		rem += va[i];
		if (rem & 1)
			res += (static_cast<uint64_t>(1) << i);
		rem >>= 1;
	}
	EXPECT_EQ(res, a * b);
}

TEST(NTTTest, NTTTestMultiplication2)
{
	uint64_t a = 0xabcd67891234, b = 0x4321;
	auto func = [](uint64_t a) -> vector<uint32_t>
	{
		vector<uint32_t> res;
		while (a)
		{
			res.push_back(a & 1);
			a >>= 1;
		}
		res.resize(64);
		return res;
	};
	vector<uint32_t> va = func(a), vb = func(b);
	NTT<uint32_t> ntt(7);
	va = ntt.transform(va, false);
	vb = ntt.transform(vb, false);
	forn(i, va.size())
		va[i] = (va[i] * vb[i]) % ntt.mod;
	va = ntt.transform(va, true);
	uint32_t rem = 0;
	uint64_t res = 0;
	forn(i, 64)
	{
		rem += va[i];
		if (rem & 1)
			res += (static_cast<uint64_t>(1) << i);
		rem >>= 1;
	}
	EXPECT_EQ(res, a * b);
}
