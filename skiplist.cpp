#include "skiplist.h"
#include "random.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// checks if the value needs to be inserted at a higher level
bool SkipList::shouldInsertAtHigherLevel() const {
  return probability >= Random::random() % 100;
}

// constructor for SkipList
SkipList::SkipList(int levels, int probability)
    : levels(levels), probability(probability) {
  head = new SNode();
  for (int i = 0; i < levels; i++) {
    head->next.push_back(nullptr);
  }
}

// copy constructor
SkipList::SkipList(const SkipList &other)
    : levels(other.levels), probability(other.probability) {
  head = new SNode();
  for (int i = 0; i < levels; i++) {
    head->next.push_back(nullptr);
  }

  unordered_map<SNode *, SNode *> nodes;
  SNode *curr = other.head->next[0];

  while (curr != nullptr) {
    nodes[curr] = new SNode();
    nodes[curr]->val = curr->val;
    curr = curr->next[0];
  }

  curr = other.head->next[0];
  while (curr != nullptr) {
    for (int j = 0; j < curr->next.size(); j++) {
      nodes[curr]->next.push_back(nodes[curr->next[j]]);
    }
    curr = curr->next[0];
  }
  for (int k = 0; k < levels; k++) {
    head->next[k] = nodes[other.head->next[k]];
  }
}

// destructor
SkipList::~SkipList() {
  SNode *curr = head;
  while (curr->next[0] != nullptr) {
    SNode *temp = curr;
    curr = curr->next[0];
    delete temp;
  }
  delete curr;
}

// collect all SNode* objects that come before this value at each level
// used as a helper function to add and remove
vector<SNode *> SkipList::getBeforeNodes(int val) const {
  SNode *curr = head;
  vector<SNode *> beforeNodes;

  for (int level = levels - 1; level >= 0; level--) {
    while (curr != nullptr && curr->next[level] != nullptr &&
           curr->next[level]->val < val) {
      curr = curr->next[level];
    }
    beforeNodes.push_back(curr);
  }
  reverse(beforeNodes.begin(), beforeNodes.end());

  return beforeNodes;
}

// Add to list, assume no duplicates
void SkipList::add(int val) {
  if (!contains(val)) {
    vector<SNode *> beforeNodes = getBeforeNodes(val);
    SNode *target = new SNode(val);

    for (int i = 0; i < levels; i++) {
      target->next.push_back(nullptr);
    }
    for (int level = 0; level < levels; level++) {
      target->next[level] = beforeNodes[level]->next[level];
      beforeNodes[level]->next[level] = target;
      if (level < levels - 1) {
        if (!shouldInsertAtHigherLevel()) {
          break;
        }
      }
    }
  }
}

// Adds vector of values to list, assume no duplicates
void SkipList::add(const vector<int> &values) {
  for (int i = 0; i < values.size(); i++) {
    add(values[i]);
  }
}

// returns true if successfully removed
bool SkipList::remove(int val) {
  vector<SNode *> beforeNodes = getBeforeNodes(val);

  if (contains(val)) {
    if (beforeNodes[0]->next[0] != nullptr &&
        beforeNodes[0]->next[0]->val == val) {
      SNode *removedNode = beforeNodes[0]->next[0];
      beforeNodes[0]->next[0] = removedNode->next[0];
      for (int level = 1; level < levels; level++) {
        if (beforeNodes[level]->next[level] == removedNode) {
          beforeNodes[level]->next[level] = removedNode->next[level];
        } else {
          break;
        }
      }
      delete removedNode;
      return (!contains(val));
    }
  }
  return false;
}

// returns true if found in SkipList
bool SkipList::contains(int val) const {
  vector<SNode *> beforeNodes = getBeforeNodes(val);

  for (int level = levels - 1; level >= 0; level--) {
    if (beforeNodes[level]->next[level] != nullptr &&
        beforeNodes[level]->next[level]->val == val) {
      return true;
    }
  }
  return false;
}

// displays skiplist with level
ostream &operator<<(ostream &out, const SkipList &skip) {
  SNode *curr = skip.head;

  for (int level = skip.levels - 1; level >= 0; level--) {
    out << "[level: " << level + 1 << "] ";
    curr = skip.head->next[level];
    while (curr != nullptr) {
      out << curr->val << "-->";
      curr = curr->next[level];
    }
    if (curr == nullptr) {
      out << "nullptr\n";
    }
  }
  return out;
}
