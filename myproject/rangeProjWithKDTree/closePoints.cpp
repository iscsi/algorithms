#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <numeric>
#include <cassert>
#include <cmath>
#include <map>
#include <set>
#include <iostream>
#include <ctime>

using namespace std;

#define FOR(k,a,b) for(int k(a); k < (b); ++k)
#define REP(k,a) for(int k=0; k < (a); ++k)
#define ABS(a) ((a)>0?(a):-(a))
#define EPS 1e-9
#define PAIR pair
#define VECTOR vector
#define ASSERT assert
typedef long long LL;
const LL MOD = 1e9 + 7;
const int INF = 1e9 + 1;

const int ParX = 0x555555;
const int ParY = 0xaaaaaa;

int highestOneBit(int x) {
	union { double a; int b[2]; };
	a = x;
	return (b[1] >> 20) - 1023;
}

class CONCAVE_HULL
{
private:
	double DistCalc(const PAIR<int, int>& a, const PAIR<int, int>& b);
	double DotProduct(const PAIR<int, int>& a, const PAIR<int, int>& b, const PAIR<int, int>& c);
	double CrossProduct(const PAIR<int, int>& a, const PAIR<int, int>& b, const PAIR<int, int>& c);
	bool CheckIntersection(const PAIR<int, int>& a, const PAIR<int, int>& b, const PAIR<int, int>& c, const PAIR<int, int>& d);
	double AngleCalc(const PAIR<int, int>& a, const PAIR<int, int>& b, const PAIR<int, int>& c);
public:
	CONCAVE_HULL(const VECTOR<PAIR<int, int> >& points, int radius, OUT VECTOR<PAIR<int, int> >& result);
};

double CONCAVE_HULL::DistCalc(const PAIR<int, int>& a, const PAIR<int, int>& b)
{
	double res = (((double)b.first) - a.first)*(b.first - a.first) + ((double)b.second - a.second)*(b.second - a.second);
	if (res < 0)
	{
		res = INF;
	}
	return sqrt(res);
}

double CONCAVE_HULL::DotProduct(const PAIR<int, int>& a, const PAIR<int, int>& b, const PAIR<int, int>& c)
{
	PAIR<int, int> ab(a.first - b.first, a.second - b.second);
	PAIR<int, int> bc(c.first - b.first, c.second - b.second);
	return (ab.first*bc.first + ab.second*bc.second) / (DistCalc(a, b)*DistCalc(b, c));
}

double CONCAVE_HULL::CrossProduct(const PAIR<int, int>& a, const PAIR<int, int>& b, const PAIR<int, int>& c)
{
	PAIR<int, int> ab(b.first - a.first, b.second - a.second);
	PAIR<int, int> bc(c.first - b.first, c.second - b.second);
	return (ab.first*bc.second - ab.second*bc.first) / (DistCalc(a, b)*DistCalc(b, c));
}

bool CONCAVE_HULL::CheckIntersection(const PAIR<int, int>& a, const PAIR<int, int>& b, const PAIR<int, int>& c, const PAIR<int, int>& d)
{
	if (a == c || a == d || b == c || b == d)
		return false;
	double ABX = b.second - a.second;
	double ABY = a.first - b.first;
	double ABZ = ABX*a.first + ABY*a.second;

	double CDX = d.second - c.second;
	double CDY = c.first - d.first;
	double CDZ = CDX*c.first + CDY*c.second;

	double det = ABX*CDY - CDX*ABY;
	if (det == 0)
	{
		return false;
	}
	double x = (CDY*ABZ - ABY*CDZ) / det;
	double y = (ABX*CDZ - CDX*ABZ) / det;
	return min(a.first, b.first) <= x && x <= max(a.first, b.first) && min(c.first, d.first) <= x && x <= max(c.first, d.first) &&
		min(a.second, b.second) <= y && y <= max(a.second, b.second) && min(c.second, d.second) <= y && y <= max(c.second, d.second);
}

double CONCAVE_HULL::AngleCalc(const PAIR<int, int>& a, const PAIR<int, int>& b, const PAIR<int, int>& c)
{
	//pifel, asin szamolgatasra nincs szukseg, mivel monoton..
	const double pifel = asin(1.0);
	double aCross = CrossProduct(a, b, c);//ha >0 ha szog kisebb mint 180
	if (aCross > 1.0)
		aCross = 1.0;
	if (aCross < -1.0)
		aCross = -1.0;
	double aDot = DotProduct(a, b, c);//ha >0 akkor a szog -90 90
	double angle = asin(aCross) * 90 / pifel;
	//angle=acos(aDot)*90/pifel;

	if (aCross >= 0 && aDot >= 0)
	{
		angle = asin(aCross) * 90 / pifel;
	}
	else if (aCross < 0 && aDot >= 0)
	{
		angle = 360 + asin(aCross) * 90 / pifel;
	}
	else if (aCross < 0 && aDot < 0)
	{
		angle = 180 - asin(aCross) * 90 / pifel;
	}
	else
	{
		angle = 180 - asin(aCross) * 90 / pifel;
		ASSERT(angle < 181 && angle>89);
	}
	return angle;
}

CONCAVE_HULL::CONCAVE_HULL(const VECTOR<PAIR<int, int> >&  points, int radius, VECTOR<PAIR<int, int> >& result)
{
	if (points.size() < 2)
		return;
	PAIR<int, int> prev, best, act = points[0];
	const double epsilon = 0.001;
	//legkisebb x coordinata megkeresese
	for (int i = 1;i < points.size();++i)
	{
		if (act > points[i])
		{
			act = points[i];
		}
	}
	prev = act;
	prev.first -= 1;
#ifdef DEBUG
	PAIR<int, int> fake = prev;
#endif // DEBUG

	result.push_back(act);
	while (result.size() < 3 || result[0] != result[result.size() - 2] || result[1] != result[result.size() - 1])
	{
		ASSERT(result.size() < 2 * points.size() + 2);
		best = prev;
		double bestAngle = 370;
		for (int i = 0;i < points.size();++i)
		{
			if (points[i] == prev || points[i] == act || DistCalc(points[i], act) > radius)
				continue;
			double angle = AngleCalc(prev, act, points[i]);
			if (angle > 30 && angle + epsilon < bestAngle /*&& checkValid(act,lPoints[i].first)*/)
			{
				bool ok = true;
				for (int j = 1;j < result.size();++j)
				{
					if (CheckIntersection(act, points[i], result[j - 1], result[j]))
					{
						ok = false;
						break;
					}
				}
				if (ok)
				{
					ASSERT(angle > 59);
					bestAngle = angle;
					best = points[i];
				}
			}
		}
		prev = act;
#ifdef DEBUG
		if (best == fake)
		{
			ASSERT(FALSE);//az elso csucs izolalt
			return;
		}
#endif // DEBUG
		act = best;
		result.push_back(act);
	}
	return;
}

struct K2DTree
{
	vector<pair<int,int> > mTree;
	void BuildTree(const vector<pair<int, int> >& points)
	{
		//points should be unique
		vector<pair<int, int> > xpoints = points, ypoints = points;
		sort(xpoints.begin(), xpoints.end());
		REP(i, ypoints.size())
		{
			swap(ypoints[i].first, ypoints[i].second);
		}
		sort(ypoints.begin(), ypoints.end());
		REP(i, ypoints.size())
		{
			swap(ypoints[i].first, ypoints[i].second);
		}
		vector< pair<vector<pair<int, int> >, vector<pair<int, int> > > > q(1, make_pair(xpoints, ypoints));
		q.reserve(points.size());
		mTree.reserve(points.size());
		REP(i, q.size())
		{
			const vector < pair<int, int> >& actx = q[i].first;
			const vector < pair<int, int> >& acty = q[i].second;
			// i+1 : 1, {2,3}, {4,5,6,7} az elso 1 es bittol fugg
			bool bX = ((i + 1)&ParX) > ((i + 1)&ParY);
			int n = actx.size();
			if(n == 0) continue;
			if (n == 1)
			{
				mTree.push_back(actx[0]);
				continue;
			}
			int pos = ( 1 << highestOneBit(n) ) - 1;
			while ( 2*pos > n - 1)
			{
				pos /= 2;
			}
			int rem = n - 1 - 2 * pos;
			rem = min(rem, pos + 1);
			pos += rem;
			pair<vector<pair<int, int> >, vector<pair<int, int> > > nq, nq2;
			if (bX)
			{
				mTree.push_back(actx[pos]);
				nq.first.assign(actx.begin(), actx.begin() + pos);
				nq2.first.assign(actx.begin()+ pos +1, actx.end());
				nq.second.reserve(nq.first.size());
				nq2.second.reserve(nq2.first.size());
				REP(j, acty.size()) if(acty[j] != actx[pos])
				{
					if (acty[j].first < actx[pos].first ||
						(acty[j].first == actx[pos].first && acty[j].second < actx[pos].second))
					{
						nq.second.push_back(acty[j]);
					}
					else
					{
						nq2.second.push_back(acty[j]);
					}
				}
			}
			else
			{
				mTree.push_back(acty[pos]);
				nq.second.assign(acty.begin(), acty.begin() + pos);
				nq2.second.assign(acty.begin() + pos + 1, acty.end());
				nq.first.reserve(nq.second.size());
				nq2.first.reserve(nq2.second.size());
				REP(j, actx.size()) if (actx[j] != acty[pos])
				{
					if (actx[j].second< acty[pos].second ||
						(actx[j].second == acty[pos].second && actx[j].first < acty[pos].first))
					{
						nq.first.push_back(actx[j]);
					}
					else
					{
						nq2.first.push_back(actx[j]);
					}
				}
			}
			assert(nq.first.size() == nq.second.size());
			assert(nq2.first.size() == nq2.second.size());
			assert(nq.first.size());
			q.emplace_back(nq);
			if(nq2.first.size())
				q.emplace_back(nq2);
		}
	}

	void StepOnTheTree(int pos, int minX, int maxX, int minY, int maxY, double d, const pair<int,int> p, vector<pair<int, int> >& v) const
	{
		if (pos >= mTree.size()) return;
		if (p.first + d + EPS < minX || p.first - d > maxX + EPS || p.second + d < minY + EPS || p.second - d > maxY + EPS)
			return;
		const pair<int, int>& act = mTree[pos];
		//calc distance
		double dd = (LL(act.first-p.first)) * (act.first-p.first) + (LL(act.second-p.second)) * (act.second-p.second);
		if (dd < d*d + 1e-9)
		{
			v.push_back(act);
		}

		//update range 
		bool bX = ((pos + 1)&ParX) > ((pos + 1)&ParY);
		if (bX)
		{
			StepOnTheTree(2 * pos + 1, minX, act.first, minY, maxY, d, p, v);
			StepOnTheTree(2 * pos + 2, act.first, maxX, minY, maxY, d, p, v);
		}
		else
		{
			StepOnTheTree(2 * pos + 1, minX, maxX, minY, act.second, d, p ,v);
			StepOnTheTree(2 * pos + 2, minX, maxX, act.second, maxY, d, p, v);
		}
	}

	vector<pair<int, int> > GetClosePoints(double d, const pair<int,int>& p)
	{
		vector<pair<int, int> > res;
		if (mTree.empty()) return res;
		StepOnTheTree(0, -INF, INF, -INF, INF, d, p, res);
		return res;
	}
	vector<pair<int, int> > GetClosePoints2(double d, const pair<int, int>& p)
	{
		vector<pair<int, int> > res;
		REP(i, mTree.size())
		{
			const pair<int, int>& act = mTree[i];
			//calc distance
			double dd = (LL(act.first - p.first)) * (act.first - p.first) + (LL(act.second - p.second)) * (act.second - p.second);
			dd = sqrt(dd);
			if (dd < d + 1e-9)
			{
				res.push_back(act);
			}
		}
		return res;
	}
};

int main(int argc, char** argv) {
#ifdef HOME
	freopen("in.txt", "rb", stdin);
	freopen("out.txt", "wb", stdout);
#endif
	vector<pair<int,int> > mp,q;
	set<pair<int, int> > s;
	clock_t start = clock();
	while(s.size() < 50000)
	{
		int x = rand() % 10000;
		int y = rand() % 10000;
		s.insert(make_pair(x, y));
		mp.push_back(make_pair(x, y));
	}

	REP(i,10000)
	{
		int x = rand() % 10000;
		int y = rand() % 10000;
		q.push_back(make_pair(x, y));
	}
	sort(mp.begin(), mp.end());
	vector<vector<pair<int, int> > > fres,fres2;
	mp.erase(unique(mp.begin(), mp.end()), mp.end());
	K2DTree kt;
	clock_t build_start = clock();
	kt.BuildTree(mp);
	clock_t kd_tree_start = clock();
	fprintf(stderr, "build time=%.3lfsec\n", 0.001*(kd_tree_start - build_start));
	REP(i,q.size())
		fres.emplace_back(kt.GetClosePoints(200, q[i]));
	clock_t bf_start = clock();
	fprintf(stderr, "kd tree time=%.3lfsec\n", 0.001*(bf_start - kd_tree_start));
	REP(i, q.size())
		fres2.emplace_back(kt.GetClosePoints2(200, q[i]));
	clock_t bf_end = clock();
	fprintf(stderr, "bf time=%.3lfsec\n", 0.001*(bf_end - bf_start));
	int not_ok = 0;
	REP(i, fres.size())
	{
		const pair<int, int>& p = q[i];
		vector<pair<int, int> > af = fres[i];
		vector<pair<int, int> > af2 = fres2[i];
		sort(af.begin(), af.end());
		sort(af2.begin(), af2.end());
		if (false)
		{
			kt.GetClosePoints(200, p);
		}
		if (af != af2)
			++not_ok;
	}
	fprintf(stderr, "not ok : %d\n",not_ok);
	return 0;
}
