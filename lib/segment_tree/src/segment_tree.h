#pragma once
#include <tools.h>

//constraints: data[0] not used, point update
//complexity: build O(N*log(N)), range query log(N), point update log(N)
//memory : 4*N 
//resource: 

template<typename T>
struct SegmentTreeLazy
{
	size_t NN; //original data size
	size_t N; //smallest two power greater or eq with NN
	size_t H; //1<<H = N : height
	vector<T> data;
	vector<T> lazy;

	void initSize()
	{
		H = static_cast<size_t>(32 - __builtin_clz(static_cast<uint32_t>(NN)));
		if ((static_cast<size_t>(1) << H) < NN)
			++H;
		N = static_cast<size_t>(1) << H;
	}

	SegmentTreeLazy(size_t S) : NN(S)
	{
		initSize();
		data.resize(2 * N, numeric_limits<T>::max());
		lazy.resize(N, static_cast<T>(0));
	}
	SegmentTreeLazy(const vector<T>& in) : NN(in.size())
	{
		initSize();
		data.resize(2 * N, numeric_limits<T>::max());
		lazy.resize(N, static_cast<T>(0));
		copy(in.begin(), in.end(), data.begin() + N);
		ford(i, N)
		{
			data[i] = min<T>(data[2 * i], data[2 * i + 1]);
		}
	}

	void propagateLazy(size_t pos)
	{
		if (lazy[pos])
		{
			if (2 * pos >= N)
			{
				data[2 * pos] += lazy[pos];
				data[2 * pos + 1] += lazy[pos];
			}
			else
			{
				lazy[2 * pos] += lazy[pos];
				lazy[2 * pos + 1] += lazy[pos];
			}
			lazy[pos] = static_cast<T>(0);
		}
	}

	void update(size_t l, size_t r, T val)
	{
		update(1, 0, N, l, r, val);
	}
	
	void update(size_t pos, size_t posL, size_t posR, size_t l, size_t r, T val)
	{
		if (r <= posL || posR <= l)
			return;
		if (posL >= l && posR <= r)
		{
			data[pos] += val;
			if (pos < N)
				lazy[pos] += val;
			return;
		}
		propagateLazy(pos);
		size_t mid = (posL + posR) / 2;
		update(2 * pos, posL, mid, l, r, val);
		update(2 * pos + 1, mid, posR, l, r, val);
		data[pos] = min<T>(data[2*pos], data[2*pos+1]);
	}

	T query(size_t l, size_t r)
	{
		return query(1, 0, N, l, r);
	}

	T query(size_t pos, size_t posL, size_t posR, size_t l, size_t r)
	{
		if (r <= posL || posR <= l)
			return static_cast<T>(numeric_limits<T>::max());//or some invalid
		if (posL >= l && posR <= r)
			return data[pos];
		propagateLazy(pos);
		size_t mid = (posL + posR) / 2;
		T q1 = query(2 * pos, posL, mid, l, r);
		T q2 = query(2 * pos + 1, mid, posR, l, r);
		return min<T>(q1, q2);
	}
};