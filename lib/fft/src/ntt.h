#pragma once
#include <tools.h>

//https://codeforces.com/blog/entry/48798

template<typename T>
struct NTT
{
	T k;
	T c;
	T mod;// = (2^k)*3+1
	T primitiveRoot;
	T prc;// (primitiveRoot^c)%mod

	NTT(T k) : k(k)
	{
		//find a modulo

		//find primitive root

		//set prc

	}

	uint32_t powMod(uint32_t v, uint32_t pw)
	{
		uint32_t res = 1;
		while (pw)
		{
			if (pw & 1)
			{
				res = (res * v) % mod;
			}
			v = (v * v) % mod;
			pw >>= 1;
		}
		return res;
	}

	uint32_t inverse(uint32_t v)
	{
		return powMod(v, mod - 2);
	}

	vector<uint32_t> transform(const vector<uint32_t>& a, bool inv)
	{
		int len = a.size();
		if (len == 1) return a;
		vector<uint32_t> f(len / 2), g(len / 2);
		for (int i = 0; i < len; i += 2)
		{
			f[i / 2] = a[i];
			g[i / 2] = a[i + 1];
		}
		
		vector<uint32_t> F = transform(f, inv), G = transform(g, inv);
		vector<uint32_t> ret(len);

		uint32_t pw = (1 << 8) / len;

		uint32_t w = powMod(prc, pw), wk = 1;
		if (inv) w = inverse(w);

		for (int i = 0; i < len / 2; ++i)
		{
			uint32_t u = F[i], v = (G[i] * wk) % mod;
			ret[i] = (u + v) % mod;
			ret[i + len / 2] = (mod + u - v) % mod;
			if (inv)
			{
				ret[i] = (ret[i] * inverse(2)) % mod;
				ret[i + len / 2] = (ret[i + len / 2] * inverse(2)) % mod;
			}
			wk = (wk * w) % mod;
		}

		return ret;
	}

	void transform2(vector<int> & a, bool invert)
	{
		int n = (int)a.size();

		for (int i = 1, j = 0; i < n; ++i) {
			int bit = n >> 1;
			for (; j >= bit; bit >>= 1)
				j -= bit;
			j += bit;
			if (i < j)
				swap(a[i], a[j]);
		}

		for (int len = 2; len <= n; len <<= 1) {
			int wlen = root;
			if (invert) wlen = inverse(root);
			for (int i = len; i < root_pw; i <<= 1)
				wlen = int(wlen * 1ll * wlen % mod);
			for (int i = 0; i < n; i += len) {
				int w = 1;
				for (int j = 0; j < len / 2; ++j) {
					int u = a[i + j], v = int(a[i + j + len / 2] * 1ll * w % mod);
					a[i + j] = u + v < mod ? u + v : u + v - mod;
					a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
					w = int(w * 1ll * wlen % mod);
				}
			}
		}
		if (invert) {
			int nrev = inverse(n);
			for (int i = 0; i < n; ++i)
				a[i] = int(a[i] * 1ll * nrev % mod);
		}
	}
};
