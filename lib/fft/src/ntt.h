#pragma once
#include <tools.h>
#include <lib/number_theory/number_theory.h>

//https://codeforces.com/blog/entry/48798

template<typename T>
struct NTT
{
	T k;
	T c;
	T mod;// = (2^k)*c+1
	T primitiveRoot;
	T prc;// (primitiveRoot^c)%mod

	NTT(T k) : k(k)
	{
		//find a prime modulo
		T step = 1 << k;
		mod = step + 1;
		while (!isPrime(mod))
			mod += step;
		c = mod / step;
		//find primitive root
		primitiveRoot = 2;
		while (!isPrimitiveRoot(primitiveRoot, mod))
			++primitiveRoot;
		//set prc
		prc = powMod(primitiveRoot, c, mod);
	}

	vector<T> transform(const vector<T>& a, bool inv)
	{
		size_t len = a.size();
		if (len == 1) return a;
		vector<T> f(len / 2), g(len / 2);
		for (T i = 0; i < len; i += 2)
		{
			f[i / 2] = a[i];
			g[i / 2] = a[i + 1];
		}
		
		vector<T> F = transform(f, inv), G = transform(g, inv);
		vector<T> ret(len);

		T pw = static_cast<T>((1ULL << k) / len);

		T w = powMod(prc, pw, mod), wk = 1;
		if (inv) w = inverse(w, mod);

		for (size_t i = 0; i < len / 2; ++i)
		{
			T u = F[i], v = (G[i] * wk) % mod;
			ret[i] = (u + v) % mod;
			ret[i + len / 2] = (mod + u - v) % mod;
			if (inv)
			{
				ret[i] = (ret[i] * inverse<T>(2, mod)) % mod;
				ret[i + len / 2] = (ret[i + len / 2] * inverse<T>(2, mod)) % mod;
			}
			wk = (wk * w) % mod;
		}

		return ret;
	}
	/*
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
	}*/
};
