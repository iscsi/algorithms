#pragma once
#include <tools.h>

//input format:
//output format: int
//constraints: sorted v vector
//complexity: log(N)
//memory : O(1)
//resource: https://codeforces.com/blog/entry/9901?#comment-153756

template<typename T>
int bin_search(const vector<T>& v, T val)
{	//return pos
	int l = -1, r = static_cast<int>(v.size());
	while (l + 1 < r)
	{
		int mid = (l + r) / 2;
		if (v[mid] <= val)
			l = mid;
		else
			r = mid;
	}
	return l;//v[l] <= val < v[r]
}
