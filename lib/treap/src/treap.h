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
			l = r = nullptr;
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
}



