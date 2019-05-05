#pragma once
#include <tools.h>

//constraints: data[0] not used, point update
//complexity: build O(N*log(N)), range query log(N), point update log(N)
//memory : 2*N 
//resource: https://codeforces.com/blog/entry/18051

template<typename T>
struct SegmentTreeBUSimple
{
	size_t N;
	vector<T> data;
	SegmentTreeBUSimple(size_t S) : N(S)
	{
		data.resize(2 * N, numeric_limits<T>::max());
	}
	SegmentTreeBUSimple(const vector<T>& in) : N(in.size())
	{
		data.resize(2*N, numeric_limits<T>::max());
		copy(in.begin(), in.end(), data.begin() + N);
		ford(i,N)
		{
			data[i] = min<T>(data[2 * i], data[2 * i + 1]);
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

//constraints: data[0] not used, range update, (N > 0,  r > 0)
//complexity: build O(N*log(N)), range query log(N), range update log(N)
//memory : 3*N
//resource: https://codeforces.com/blog/entry/18051

template<typename T>
struct SegmentTreeBULazy
{
	size_t N;
	vector<T> data;
	vector<T> lazy;
	SegmentTreeBULazy(size_t S) : N(S)
	{
		data.resize(2 * N, numeric_limits<T>::max());
		lazy.resize(N, static_cast<T>(0));
	}
	SegmentTreeBULazy(const vector<T>& in) : N(in.size())
	{
		data.resize(2 * N, numeric_limits<T>::max());
		lazy.resize(N, static_cast<T>(0));
		copy(in.begin(), in.end(), data.begin() + N);
		ford(i, N)
		{
			data[i] = min<T>(data[2 * i], data[2 * i + 1]);
		}
	}

	void apply(size_t pos, T value)
	{
		data[pos] += value;
		if (pos < N)
			lazy[pos] += value;
	}

	void build(size_t pos)
	{
		while (pos) // why not just if??
		{
			pos >>= 1;
			data[pos] = min<T>(data[2 * pos], data[2 * pos + 1]) + lazy[pos];
		}
	}

	void modify(size_t l, size_t r, T value)
	{  // modify [l,r) by value
		l += N, r += N;
		for (size_t nl = l, nr = r; nl < nr; nl >>= 1, nr >>= 1)
		{
			if (nl & 1)
				apply(nl++, value);
			if (nr & 1)
				apply(--nr, value);
		}
		build(l);
		build(r - 1);
	}

	void push(size_t pos)
	{
		if (pos == 0)
			return;
		push(pos / 2);
		if (lazy[pos] != 0)
		{
			apply(2 * pos, lazy[pos]);
			apply(2 * pos + 1, lazy[pos]);
			lazy[pos] = 0;
		}
	}

	T query(size_t l, size_t r)
	{  // min on interval [l, r)
		l += N, r += N;
		push(l / 2);
		push((r - 1) / 2);
		T res = numeric_limits<T>::max();
		for (; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1) res = min<T>(res, data[l++]);
			if (r & 1) res = min<T>(res, data[--r]);
		}
		return res;
	}
};

