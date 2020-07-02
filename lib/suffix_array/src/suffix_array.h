#pragma once
#include <tools.h>

vector<uint32_t> suffixArray(const string& inStr)
{
	const string str = inStr + '$';
	uint32_t n = str.length();
	vector<uint32_t> p(n);
	vector<uint32_t> c(n);

	{//k = 0 case
		vector<pair<char, uint32_t> > a(n);
		forn(i, n)
			a[i] = { str[i], i };

		sort(all(a));
		forn(i, n)
			p[i] = a[i].second;
		c[p[0]] = 0;
		for1(i, n)
		{
			if (a[i].first == a[i - 1].first)
			{
				c[p[i]] = c[p[i - 1]];
			}
			else
			{
				c[p[i]] = c[p[i - 1]] + 1;
			}
		}
	}
	int k = 0;
	while ((1 << k) < n)
	{ // k -> k + 1
		vector<pair<pair<uint32_t, uint32_t>, uint32_t> > a(n);
		forn(i, n)
			a[i] = { { c[i], c[(i+(1<<k))%n]}, static_cast<uint32_t>(i)};

		sort(all(a));
		forn(i, n)
			p[i] = a[i].second;
		c[p[0]] = 0;
		for1(i, n)
		{
			if (a[i].first == a[i - 1].first)
			{
				c[p[i]] = c[p[i - 1]];
			}
			else
			{
				c[p[i]] = c[p[i - 1]] + 1;
			}
		}
		k++;
	}
	return p;
}