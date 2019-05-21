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
	
	//without recursion
	void transform2(vector<T> & a, bool inv)
	{
		size_t n = a.size();

		for (size_t i = 1, j = 0; i < n; ++i) 
		{
			size_t bit = n >> 1;
			while (j >= bit)
			{
				j -= bit;
				bit >>= 1;
			}
			j += bit;
			if (i < j)
				swap(a[i], a[j]);
		}

		for (size_t len = 2; len <= n; len <<= 1) 
		{
			T pw = static_cast<T>((1ULL << k) / len);
			T wlen = powMod(prc, pw, mod);
			if (inv) wlen = inverse(wlen, mod);
			for (size_t i = 0; i < n; i += len) 
			{
				T w = 1;
				for (size_t j = 0; j < len / 2; ++j) 
				{
					T u = a[i + j], v = (a[i + j + len / 2] * w) % mod;
					a[i + j] = u + v < mod ? u + v : u + v - mod;
					a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
					w = (w * wlen) % mod;
				}
			}
		}
		if (inv) 
		{
			T nrev = inverse(static_cast<T>(n), mod);
			for (int i = 0; i < n; ++i)
				a[i] = (a[i] * nrev) % mod;
		}
	}
};
