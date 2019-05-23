#pragma once
#include <tools.h>

//constraints: 
//complexity: split O(log(N)), meld log(N)
//resource: https://threads-iiith.quora.com/Treaps-One-Tree-to-Rule-em-all-Part-1

namespace Treap 
{

	struct Node;
	typedef Node* pNode;

	struct Node
	{
		uint32_t value;
		uint32_t priority;

		//additional structures
		uint32_t size = 0;

		pNode left;
		pNode right;

		Node(uint32_t val) : 
			value(val), 
			priority(getRandom<uint32_t>(0, numeric_limits<uint32_t>::max())),
			left(nullptr),
			right(nullptr){}
	};

	uint32_t getSize(pNode t)
	{
		return t == nullptr ? 0 : t->size;
	}

	void updateSize(pNode t)
	{
		if(t != nullptr)
			t->size = getSize(t->left) + 1 + getSize(t->right);
	}

	void split(pNode t, pNode& l, pNode& r, uint32_t key)
	{
		if (t == nullptr)
		{
			l = r = nullptr;
		}
		else if (t->value <= key)
		{
			split(t->right, t->right, r, key);
			l = t;
		}
		else
		{
			split(t->left, l, t->left, key);
			r = t;
		}
		updateSize(t);
	}

	void meld(pNode& t, pNode l, pNode r)
	{
		if (l == nullptr || r == nullptr)
		{
			t = l == nullptr ? r : l;
		}
		else if (l->priority > r->priority)
		{
			meld(l->right, l->right, r);
			t = l;
		}
		else
		{
			meld(r->left, l, r->left);
			t = r;
		}
		updateSize(t);
	}

	void insert(pNode& t, pNode newNode)
	{
		if (t == nullptr)
		{
			t = newNode;
		}
		else if (newNode->priority > t->priority)
		{
			split(t, newNode->left, newNode->right, newNode->value);
			t = newNode;
		}
		else
		{
			if (t->value <= newNode->value)
				insert(t->right, newNode);
			else
				insert(t->left, newNode);
		}
		updateSize(t);
	}

	void erase(pNode& t, uint32_t key)
	{
		if (t == nullptr)
			return;
		if (t->value == key)
		{
			pNode tmp = t;
			meld(t, t->left, t->right);
			delete tmp;
		}
		else
		{
			if (t->value < key)
				erase(t->right, key);
			else
				erase(t->left, key);
		}
		updateSize(t);
	}

	pNode getNewNode(uint32_t val)
	{
		return new Node(val);
	}

	uint32_t getCount(pNode& t, uint32_t key)
	{
		if (t == nullptr)
			return 0;
		if (t->value < key)
			return getCount(t->right, key);
		if (t->value > key)
			return getCount(t->left, key);
		return getCount(t->left, key) + 1 + getCount(t->right, key);
	}
}

struct TreapNode;

struct TreapPool
{
	vector<TreapNode> mData;
	vector<uint32_t> mRemainQueue;
	void init(uint32_t newSize);
	uint32_t get();
	void release(uint32_t v);
};

struct TreapNode
{
	static TreapPool mPool;

	uint32_t value;
	uint32_t priority;

	//additional structures
	uint32_t size = 0;

	uint32_t myId;
	uint32_t leftId;
	uint32_t rightId;

	TreapNode(uint32_t val = 0) :
		value(val),
		priority(getRandom<uint32_t>(0, numeric_limits<uint32_t>::max())),
		leftId(0),
		rightId(0)//,
		//myId(mPool.get())
	{}

	~TreapNode()
	{
		clear();
	}

	void clear()
	{
		myId = leftId = rightId = size = value = 0;
	}

	uint32_t getSize() const
	{
		return size;
	}

	void updateSize(uint32_t t)
	{
		if (t)
		{
			TreapNode& tn = mPool.mData[t];
			tn.size = mPool.mData[tn.leftId].getSize() + 1 + mPool.mData[tn.rightId].getSize();
		}
	}

	void split(uint32_t t, uint32_t& l, uint32_t& r, uint32_t key)
	{
		TreapNode& tn = mPool.mData[t];
		if (t == 0)
		{
			l = r = 0;
		}
		else if ( tn.value <= key)
		{
			split(tn.rightId, tn.rightId, r, key);
			l = t;
		}
		else
		{
			split(tn.leftId, l, tn.leftId, key);
			r = t;
		}
		updateSize(t);
	}
	void meld(uint32_t& t, uint32_t l, uint32_t r)
	{
		TreapNode& tn = mPool.mData[t];
		TreapNode& ln = mPool.mData[l];
		TreapNode& rn = mPool.mData[r];

		if (l == 0 || r == 0)
		{
			t = l == 0 ? r : l;
		}
		else if (ln.priority > rn.priority)
		{
			meld(ln.rightId, ln.rightId, r);
			t = l;
		}
		else
		{
			meld(rn.leftId, l, rn.leftId);
			t = r;
		}
		updateSize(t);
	}

	void insert(uint32_t& t, uint32_t newNodeId)
	{
		TreapNode& tn = mPool.mData[t];
		TreapNode& nn = mPool.mData[newNodeId];
		if (t == 0)
		{
			t = newNodeId;
		}
		else if (nn.priority > tn.priority)
		{
			split(t, nn.leftId, nn.rightId, nn.value);
			t = newNodeId;
		}
		else
		{
			if (tn.value <= nn.value)
				insert(tn.rightId, newNodeId);
			else
				insert(tn.leftId, newNodeId);
		}
		updateSize(t);
	}

	void erase(uint32_t& t, uint32_t key)
	{
		if (t == 0)
			return;
		TreapNode& tn = mPool.mData[t];
		if (tn.value == key)
		{
			meld(t, tn.leftId, tn.rightId);
			mPool.release(t);
			return;
		}
		else
		{
			if (tn.value < key)
				erase(tn.rightId, key);
			else
				erase(tn.leftId, key);
		}
		updateSize(t);
	}

	uint32_t getCount(const uint32_t& t, uint32_t key) const
	{
		if (t == 0)
			return 0;
		const TreapNode& tn = mPool.mData[t];
		if (tn.value < key)
			return getCount(tn.rightId, key);
		if (tn.value > key)
			return getCount(tn.leftId, key);
		return getCount(tn.leftId, key) + 1 + getCount(tn.rightId, key);
	}
};

void TreapPool::init(uint32_t newSize)
{
	mData.clear();
	mRemainQueue.clear();
	mData.resize(newSize);
	mRemainQueue.resize(newSize);
	for1(i, newSize-1)
	{
		mRemainQueue[i] = i;
	}
	reverse(all(mRemainQueue));
}

uint32_t TreapPool::get()
{
	uint32_t res = mRemainQueue.back();
	mRemainQueue.pop_back();
	return res;
}
void TreapPool::release(uint32_t v)
{
	mData[v].clear();
	mRemainQueue.push_back(v);
}

TreapPool TreapNode::mPool;
