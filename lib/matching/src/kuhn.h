#pragma once
#include <tools.h>

//Kuhn O(V*E)
//https://sites.google.com/site/indy256/algo/kuhn_matching2


int maxMatching(const vector<vector<int> >& g, int B)
{
	size_t A = g.size();
	vector<int> matching(B, -1);
	int res = 0;
	vector<bool> vis(A, false);

	function<bool(int)> findPath = [&](int nodeId) -> bool {
		vis[nodeId] = true;
		for (int BSideId : g[nodeId])
		{
			int u = matching[BSideId];
			if (u == -1 || (!vis[u] && findPath(u)))
			{
				matching[BSideId] = nodeId;
				return true;
			}
		}
		return false;
	};

	forn(u, A)
	{
		fill(all(vis), false);
		if (findPath(u))
			++res;
	}
	return res;
}
