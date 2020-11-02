#pragma once
#include <tools.h>

int push_relabel(const vector<vector<int> >& g)
{
	//N-2 th index source, N-1 target
	int N = g.size();
	int source = N - 2;
	//calc
	vector<vector<int> > res = g;

	vector<vector<int> > preflow(N, vector<int>(N));

	vector<int> e(N);
	vector<int> h(N);

	h[source] = N;

	forn(i, N)
	{
		if (res[source][i] > 0)
		{
			res[source][i] = 0;
			res[i][source] = g[source][i];
			preflow[source][i] = g[source][i];
			e[i] += g[source][i];
		}
	}

	int ctr = 1;
	while (ctr)
	{
		ctr = 0;
		forn(i, source) if (e[i])
		{
			++ctr;
			bool found = false;
			int mir = 2 * N;
			forn(j, N)
			{
				if (res[i][j] && h[i] == h[j] + 1)
				{
					int mi = min(res[i][j], e[i]);
					if (preflow[j][i] == 0)
						preflow[i][j] += mi;
					else
						preflow[j][i] -= mi;
					res[i][j] -= mi;
					res[j][i] += mi;
					e[i] -= mi;
					e[j] += mi;
					found = true;
				}
				if (res[i][j])
				{
					mir = min(mir, h[j] + 1);
				}
			}
			if (!found)
				h[i] = mir;
		}
	}
	int answer = 0;
	forn(i, source)
		answer += preflow[source][i];
	return answer;
}