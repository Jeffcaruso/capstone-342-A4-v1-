#include "skiplist.h"
#include "random.h"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

using namespace std;

// checks if the value needs to be inserted at a higher level
bool SkipList::shouldInsertAtHigherLevel() const
{
	return probability >= Random::random() % 100;
}

// you code goes here

SkipList::~SkipList()
{
	return;
}

void SkipList::add(int val)
{
	return;
}

void SkipList::add(const vector<int> &values)
{
	return;
}

bool SkipList::remove(int val)
{
	return false;
}

bool SkipList::contains(int val) const
{
	return false;
}

ostream &operator<<(ostream &out, const SkipList &skip)
{
	// TODO: insert return statement here
	return out;
}
