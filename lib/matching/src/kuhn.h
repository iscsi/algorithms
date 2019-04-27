#pragma once
#include <tools.h>

//Kuhn O(V*E)
//https://sites.google.com/site/indy256/algo/kuhn_matching2

bool findPath(const vector<vector<int> >& g, int nodeId, vector<int>& matching, vector<bool>& vis)
{
	vis[nodeId] = true;
	for (int BSideId : g[nodeId])
	{
		int u = matching[BSideId];
		if (u == -1 || (!vis[u] && findPath(g, u, matching, vis)))
		{
			matching[BSideId] = nodeId;
			return true;
		}
	}
	return false;
}

int maxMatching(const vector<vector<int> >& g, int B)
{
	int A = g.size();
	vector<int> matching(B, -1);
	int res = 0;
	forn(u, A)
	{
		vector<bool> vis(A, false);
		if (findPath(g, u, matching, vis))
			++res;
	}
	return res;
}
