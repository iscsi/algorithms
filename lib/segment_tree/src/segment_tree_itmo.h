#pragma once
#include <tools.h>

//recursive solution
//3 case : 
//1: outside
//2: inside
//3: intersect : the corresponding segment contains l or r => complexity log n

//left child 2x+1, right child 2x+2

template<typename T>
struct SegmentTreeITMO {
	int size;
	vector<T> data;

	void init(int n) {
		size = 1;
		while (size < n)
			size *= 2;
		data.assign(2 * size, T());
	}

	void build(const vector<T>& a, int x, int lx, int rx) {
		if (rx == lx + 1) {
			if (lx < (int)a.size()) {
				data[x] = a[lx];
			}
			return;
		}
		int m = (lx + rx) / 2;
		build(a, 2 * x + 1, lx, m);
		build(a, 2 * x + 2, m, rx);
		data[x] = data[2 * x + 1] + data[2 * x + 2];
	}

	void build(const vector<T>& a) {
		build(a, 0, 0, size);
	}

	//index, value, current node, left border, right border
	void set(int idx, T v, int x, int lx, int rx) {
		if (rx == lx + 1) {
			//the bottom level
			data[x] = v;
			return;
		}
		int m = (lx + rx) / 2;
		if (idx < m) {
			set(idx, v, 2 * x + 1, lx, m);
		}
		else {
			set(idx, v, 2 * x + 2, m, rx);
		}
		//the operation + here
		data[x] = data[2 * x + 1] + data[2 * x + 2];
	}

	void set(int idx, T v) {
		set(idx, v, 0, 0, size);
	}
	T get(int l, int r, int x, int lx, int rx) {
		if (lx >= r || rx <= l) return 0;//outside
		if (lx >= l && rx <= r) return data[x];
		int m = (lx + rx) / 2;
		T r1 = get(l, r, 2 * x + 1, lx, m);
		T r2 = get(l, r, 2 * x + 2, m, rx);
		return r1 + r2;//the operation
	}

	T get(int l, int r) {
		return get(l, r, 0, 0, size);
	}
};