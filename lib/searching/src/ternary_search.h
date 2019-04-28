#pragma once
#include <tools.h>

//input format:
//output format: long double
//constraints: (strictly) unimodal function ( /\ or \/ )
//complexity: log(N)
//memory : O(1)
//resource1: https://codeforces.com/blog/entry/60702
//resource2: https://codeforces.com/blog/entry/43440
//resource3: https://codeforces.com/blog/entry/11497
//resource4: https://apps.topcoder.com/forums/?module=Thread&threadID=670169&start=0

template<typename T>
long double ternary_search(std::function<T(long double)> f, long double A, long double B)
{	//return minimum pos
	const long double EPS = 1e-15;
	while (A + EPS < B)
	{
		long double m1 = (A * 2 + B) / 3;
		long double m2 = (A + B * 2) / 3;
		if (f(m1) > f(m2))
			A = m1;
		else
			B = m2;
	}
	return A;
}

//input format: minimum [A,B]
//output format: integral
//constraints: unimodal function ( /\ or \/ )

template<typename T>
int64_t ternary_searchInt(std::function<T(int64_t)> f, int64_t A, int64_t B)
{	//return minimum pos
	while (A + 1 < B)
	{
		int64_t mid = (A + B) / 2;
		if (f(mid) < f(mid + 1))
			B = mid;
		else
			A = mid + 1;
	}
	return f(A)<f(B)? A : B;
}

