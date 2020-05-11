#pragma once
#include <tools.h>

struct SCC 
{
	vector<vector<size_t>> neighboorList;
	vector<vector<size_t>> neighboorReversedList;
	vector<size_t> componentId;
	
	SCC(const vector<vector<size_t>>& neigh) : neighboorList(neigh){
		auto N = neighboorList.size();
		neighboorReversedList.resize(N);
		forn(i, N)
		{
			for(auto neigh : neighboorList[i])
			{
				neighboorReversedList[neigh].push_back(i);
			}
		}
	}
	
	void calculateComponents()
	{
		auto N = neighboorList.size();
		size_t componentCounter = 0;
		
		vector<size_t> order;
		vector<bool> used(N);
		componentId.resize(N);

		function<void(size_t)> dfs1 = [&](size_t v) {
			used[v] = true;
			const auto& actNeighboorList = neighboorList[v];
			forn(i, actNeighboorList.size())
			{
				auto candidate = actNeighboorList[i];
				if (!used[candidate])
				{
					dfs1(candidate);
				}
			}
			order.push_back(v);
		};

		function<void(size_t)> dfs2 = [&](size_t v) {
			used[v] = true;
			componentId[v] = componentCounter;
			const auto& actNeighboorReversedList = neighboorReversedList[v];
			forn(i, actNeighboorReversedList.size())
			{
				auto candidate = actNeighboorReversedList[i];
				if (!used[candidate])
				{
					dfs2(candidate);
				}
			}
		};

		forn(i, N)
		{
			if (!used[i])
				dfs1(i);
		}
		
		reverse(all(order));
		fill(all(used), false);

		for(auto v: order)
		{
			if (!used[v])
			{
				dfs2(v);
				++componentCounter;
			}
				
		}
	}
};