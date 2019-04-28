#pragma once
#include <tools.h>

//constraints: point update
//complexity: inc log(N), prefix sum log(N)
//memory : N 

template<typename T>
struct FenwickTree
{
	vector<T> data;
	void init(size_t n)
	{
		data.resize(n);
	}
	void init(const vector<T>& v)
	{
		data.resize(v.size());
		forn(i, v.size())
			inc(i, v[i]);
	}
	void inc(size_t pos, T val)
	{
		for (; pos < data.size(); pos |= pos + 1)
		{
			data[pos] += val;
		}
	}
	T sum(size_t pos) const
	{
		T ret = 0;
		for(++pos; pos; pos&=pos-1)
		{
			ret += data[pos-1];
		}
		return ret;
	}
};
