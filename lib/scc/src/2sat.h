#pragma once
#include <tools.h>

struct CLAUSE
{
	size_t id1;
	size_t id2;
	bool coeff1;
	bool coeff2;

	CLAUSE(bool _coeff1, size_t _id1, bool _coeff2, size_t _id2):
		coeff1(_coeff1),
		id1(_id1),
		coeff2(_coeff2),
		id2(_coeff2){}
	CLAUSE(initializer_list<pair<bool, size_t>> lst)
	{
		assert(lst.size() == 2);
		auto it = lst.begin();
		coeff1 = it->first;
		id1 = it->second;
		++it;
		coeff2 = it->first;
		id2 = it->second;
	}
	bool calc(const vector<bool>& assignment)
	{
		return	(coeff1 ? assignment[id1] : !assignment[id1]) | 
				(coeff2 ? assignment[id2] : !assignment[id2]);
	}
};

struct SAT2
{
	vector<bool> Calculate(int N, const vector<CLAUSE>& cnf)
	{
		vector <bool> assignment(N);
		vector<vector<size_t>> g(2*N);
		for (auto cl : cnf)
		{
			size_t u = 2 * cl.id1 + (cl.coeff1 ? 1 : 0);
			size_t v = 2 * cl.id2 + (cl.coeff2 ? 1 : 0);
			g[u].push_back(v ^ 1);
			g[v].push_back(u ^ 1);
		}
		SCC scc(g);
		scc.calculateComponents();
		
		forn(i, N)
		{
			if (scc.componentId[2 * i] == scc.componentId[2 * i + 1])
				return vector<bool>();
			assignment[i] = scc.componentId[2 * i] > scc.componentId[2 * i + 1];
		}
		return assignment;
	}
};