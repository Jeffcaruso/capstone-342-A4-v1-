/**
 * SkipList class
 * SkipList data structure for insertion, deletion, and search operations on a
 * sorted set of integers in O(log n) time
 */

#include "skiplist.h"
#include "random.h"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <unordered_map>

using namespace std;

// SNode constructor
// initializes a SNode object with the given integer value
SNode::SNode(int val) : val(val), next(1, nullptr){};

// SNode copy constructor
// creates a deep copy of another SNode object
SNode::SNode(const SNode &other) : val(other.val) {
  next = vector<SNode *>(other.next.size());

  for (int i = 0; i < next.size(); i++) {
    if (next[i] != nullptr) {
      next[i] = new SNode(*other.next[i]);
    }
  }
}

// SkipList constructor
// initializes a SkipList object with the given levels and probability
SkipList::SkipList(int levels, int probability)
    : levels(levels), probability(probability) {
  head = new SNode();
  head->next.resize(levels, nullptr);
}

// SkipList copy constructor
// creates a deep copy of another SkipList object
SkipList::SkipList(const SkipList &other)
    : levels(other.levels), probability(other.probability) {
  unordered_map<SNode *, SNode *> nodeMap;

  head = new SNode(*other.head);
  head->next.resize(levels, nullptr);

  for (int i = levels - 1; i >= 0; i--) {
    SNode *curr = other.head->next[i];
    SNode *prev = head;

    while (curr != nullptr) {
      if (nodeMap.count(curr) == 0) {
        SNode *copy = new SNode(*curr);
        nodeMap[curr] = copy;
      }

      prev->next[i] = nodeMap[curr];
      prev = prev->next[i];

      curr = curr->next[i];
    }
  }
}

// SkipList destructor
SkipList::~SkipList() {
  SNode *curr = head->next[0];
  SNode *next = nullptr;

  while (curr != nullptr) {
    next = curr->next[0];
    delete curr;
    curr = next;
  }

  delete head;
  head = nullptr;
}

// operator<< to display SkipList levels and values
ostream &operator<<(ostream &out, const SkipList &skip) {
  for (int i = skip.levels - 1; i >= 0; i--) {
    out << "[level: " << i + 1 << "] ";

    SNode *curr = skip.head->next[i];
    while (curr != nullptr) {
      out << curr->val << "-->";
      curr = curr->next[i];
    }
    out << "nullptr\n";
  }
  return out;
}

// checks if the value needs to be inserted at a higher level
bool SkipList::shouldInsertAtHigherLevel() const {
  return probability >= Random::random() % 100;
}

// collects all SNode* objects that come before this value at each level
// used as a helper funnction to add and remove
vector<SNode *> SkipList::getBeforeNodes(int val) const {
  vector<SNode *> beforeNodes(levels, head);

  SNode *curr = head;

  for (int i = levels - 1; i >= 0; i--) {
    while (curr->next[i] != nullptr && curr->next[i]->val < val) {
      curr = curr->next[i];
    }
    beforeNodes[i] = curr;
  }

  return beforeNodes;
}

// adds a single value to SkipList, assumes no duplicates
void SkipList::add(int val) {
  vector<SNode *> beforeNodes = getBeforeNodes(val);

  SNode *newNode = new SNode(val);
  newNode->next.push_back(nullptr);

  newNode->next[0] = beforeNodes[0]->next[0];
  beforeNodes[0]->next[0] = newNode;

  for (int nodeLevel = 1; nodeLevel < levels; nodeLevel++) {
    if (shouldInsertAtHigherLevel()) {
      if (nodeLevel >= newNode->next.size()) {
        newNode->next.push_back(nullptr);
      }

      newNode->next[nodeLevel] = beforeNodes[nodeLevel]->next[nodeLevel];
      beforeNodes[nodeLevel]->next[nodeLevel] = newNode;
    } else {
      break;
    }
  }
}

// adds multiple values to SkipList, assumes no duplicates
void SkipList::add(const vector<int> &values) {
  for (int i = 0; i < values.size(); i++) {
    add(values[i]);
  }
}

// returns true if successfully removed, otherwise false
bool SkipList::remove(int val) {
  if (!contains(val)) {
    return false;
  }

  vector<SNode *> beforeNodes = getBeforeNodes(val);

  SNode *removedNode = beforeNodes[0]->next[0];

  for (int i = 0; i < beforeNodes.size(); i++) {
    if (beforeNodes[i]->next[i]->val == val) {
      beforeNodes[i]->next[i] = removedNode->next[i];
    }
  }

  delete removedNode;
  removedNode = nullptr;

  return true;
}

// returns true if value is found in Skiplist, otherwise false
bool SkipList::contains(int val) const {
  vector<SNode *> beforeNodes = getBeforeNodes(val);

  for (int i = levels - 1; i >= 0; i--) {
    if (beforeNodes[i]->next[i] != nullptr &&
        beforeNodes[i]->next[i]->val == val) {
      return true;
    }
  }

  return false;
}
