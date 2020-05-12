#pragma once
#include <tools.h>

//Kuhn O(V*E)
//https://sites.google.com/site/indy256/algo/kuhn_matching2
//http://codeforces.com/blog/entry/17534

pair<vector<bool>, vector<bool> > minVertexCover(const vector<vector<int> >& g, int B)
{
	size_t A = g.size();
	vector<int> matching(B, -1);
	vector<bool> vis(A, false);
	function<bool(int)> findPath = [&](int nodeId) {
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
		findPath(u);
	}
	//orientate the mathing edges B to A all other A to B
	//start dfs vertecies which not present in the matching
	//min vertex cover is all visited in B&matching u not visited A&matching
	vector<bool> visA(A,1), visB(B,1);
	vector<pair<int, int> > q;
	forn(i, B) if (matching[i] != -1)
			visA[matching[i]]=0, visB[i] = 0;
	forn(i, A) if (visA[i])
		q.push_back(make_pair(i, 0));
	forn(i, B) if (visB[i])
		q.push_back(make_pair(i, 1));
	forn(i, q.size())
	{
		int actId = q[i].first;
		int actSide = q[i].second;
		if (actSide) //B side
		{
			if (matching[actId] != -1 && !visA[matching[actId]] )
			{
				visA[matching[actId]] = 1;
				q.push_back(make_pair(matching[actId], 0));
			}
		}
		else
		{
			forn(j, g[actId].size())
			{
				int other = g[actId][j];
				if (!visB[other] && matching[other] != i)
				{
					visB[other] = 1;
					q.push_back(make_pair(other, 1));
				}
			}
		}
	}
	vector<bool> ASide(A), BSide(B);
	forn(i, B) if (matching[i] != -1)
	{
		if (visB[i])
			BSide[i] = 1;
		if (!visA[matching[i]])
			ASide[matching[i]] = 1;
	}
	return make_pair(ASide, BSide);
}
