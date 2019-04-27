#pragma once
#include <tools.h>

//input format:
//output format:
//constraints: data[0] not used, point update
//complexity: build O(N*log(N)), query log(N), update log(N)
//memory : O(N*log(N))
//resource: https://codeforces.com/blog/entry/18051

template<typename T>
struct SegmentTree
{
	size_t N;
	vector<T> data;
	SegmentTree(size_t S) : N(S)
	{
		data.resize(2 * N, numeric_limits<T>::max());
	}
	SegmentTree(const vector<T>& in) : N(in.size())
	{
		data.resize(2*N, numeric_limits<T>::max());
		copy(in.begin(), in.end(), data.begin() + N);
		ford(i,N)
		{
			data[i] = min<T>(data[i << 1], data[i << 1 | 1]);
		}
	}

	void modify(size_t pos, T value) 
	{  // set value at position pos
		for (data[pos += N] = value; pos > 1; pos >>= 1)
		{
			data[pos >> 1] = min<T>(data[pos], data[pos ^ 1]);
		}
	}

	T query(size_t l, size_t r) 
	{  // min on interval [l, r)
		T res = numeric_limits<T>::max();
		for (l += N, r += N; l < r; l >>= 1, r >>= 1) 
		{
			if (l & 1) res = min<T>(res, data[l++]);
			if (r & 1) res = min<T>(res, data[--r]);
		}
		return res;
	}
};
