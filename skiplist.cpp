#include "skiplist.h"
#include "random.h"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <unordered_set>

using namespace std;

// SNode constructor
SNode::SNode(int val) { this->val = val; }

// ostream
ostream &operator<<(ostream &out, const SkipList &skip) {

  // loops through all levels
  for (int i = skip.levels; i > 0; i--) {
    out << "[level:" << i << "] ";

    // current iterating node starts at the beginning of each level
    SNode *current = (skip.head->next)[i - 1];

    // ends when it hits a "null pointer"
    while (!(current->isNullPtr)) {
      out << current->val << "-->";
      current = (current->next)[i - 1];
    }

    out << "nullptr\n";
  }

  return out;
}

// SkipList deconstructor
SkipList::~SkipList() {
  // add in head first
  deleteSNodes.insert(head);

  // iterate through all levels
  for (int i = 0; i < levels; i++) {
    // current iterating node starts at the beginning of each level
    SNode *current = (head->next)[i];

    while (!(current->isNullPtr)) {
      deleteSNodes.insert(current);

      // insert any unused "null pointer" nodes
      for (SNode *nullptrSNode : current->next) {
        deleteSNodes.insert(nullptrSNode);
      }

      current = (current->next)[i];
    }

    // there is a "null pointer" node at the end of each level
    deleteSNodes.insert(current);
  }

  // delete all nodes
  for (SNode *deleteSNode : deleteSNodes) {
    delete deleteSNode;
  }
}

// SkipList constructor
SkipList::SkipList(int levels, int probability) {
  this->levels = levels;
  this->probability = probability;

  head = new SNode();

  // all levels end with a "null pointer" node
  for (int i = 0; i < levels; i++) {
    SNode *newSNode = new SNode();
    newSNode->isNullPtr = true;
    (head->next).push_back(newSNode);
  }
}

// SkipList copy constructor
SkipList::SkipList(const SkipList &other) {
  SNode *current;       // current iterating node
  SNode *previousLevel; // current iterating previous level node
  SNode *currentCopy = (other.head->next)[0]; // current copy iterating node

  // copy probability and level number
  levels = other.levels;
  probability = other.probability;

  // start with the head
  head = new SNode();
  current = head;

  // copy first level
  while (!(currentCopy->isNullPtr)) {
    (current->next).push_back(new SNode(currentCopy->val));
    current = (current->next)[0];
    currentCopy = (currentCopy->next)[0];
  }

  // add a "null pointer"
  (current->next).push_back(new SNode());
  (current->next)[0]->isNullPtr = true;

  // copy the rest of the levels
  for (int i = 2; i <= levels; i++) {
    current = head;
    currentCopy = (other.head->next)[i - 1];
    previousLevel = (head->next[i - 2]);

    while (!(currentCopy->isNullPtr)) {
      if ((previousLevel->val) == (currentCopy->val)) {
        // connect to previous level
        (current->next).push_back(previousLevel);
        current = (current->next)[i - 1];
        previousLevel = (previousLevel->next)[i - 2];
        currentCopy = (currentCopy->next)[i - 1];
      }
      // if the previous level node does not extend another level, move on
      else {
        previousLevel = (previousLevel->next)[i - 2];
      }
    }

    // add "null pointer"
    (current->next).push_back(new SNode());
    (current->next)[i - 1]->isNullPtr = true;
  }

  // add extra link nodes ("null ptrs") for every node
  for (int i = 0; i < levels; i++) {
    current = (head->next)[i];
    while (!(current->isNullPtr)) {
      for (int j = (current->next).size(); j <= levels; j++) {
        SNode *newSNode = new SNode();
        newSNode->isNullPtr = true;
        (current->next).push_back(newSNode);
      }
      current = (current->next)[i];
    }
  }
}

// checks if the value needs to be inserted at a higher level
bool SkipList::shouldInsertAtHigherLevel() const {
  return probability >= Random::random() % 100;
}

// add multiple numbers into the skiplist
void SkipList::add(const vector<int> &values) {
  for (int value : values) {
    add(value);
  }
}

// add a number into the skiplist
void SkipList::add(int val) {
  int currentLevel = 0; // current level to be iterated through
  vector<SNode *> before = getBeforeNodes(val); // vector of nodes that will
                                                // link to the added node
  SNode *newSNode = new SNode(val);             // node that will be added

  // every node will have a link to another node corresponding to each level
  for (int i = 0; i < levels; i++) {
    (newSNode->next).push_back(new SNode());
    (newSNode->next)[i]->isNullPtr = true;
  }

  // every node has a 100% chance of being inserted in the first level
  do {
    currentLevel = currentLevel + 1;

    // node to be deleted from the added node
    SNode *deleteSNode = (newSNode->next)[currentLevel - 1];

    // replace the to be deleted node
    (newSNode->next)[currentLevel - 1] =
        (before[currentLevel - 1]->next)[currentLevel - 1];

    // change the link of the previous node
    (before[currentLevel - 1]->next)[currentLevel - 1] = newSNode;

    // delete the to be deleted node
    delete deleteSNode;

    // chance of a number being inserted at a higher level determined by
    // probability
  } while (currentLevel < levels && shouldInsertAtHigherLevel());
}

// get nodes that link to a node containing a certain number
vector<SNode *> SkipList::getBeforeNodes(int val) const {
  int currentLevel = levels; // current level to be iterated through
  vector<SNode *> before;    // vector of nodes that will change their links
  SNode *current = head;     // iterating current node

  // all nodes link to the head
  for (int i = 0; i < levels; i++) {
    before.push_back(head);
  }

  // iterate through the levels, starting with the topmost
  while (currentLevel > 0) {
    // constantly update the vector of nodes to contain the closest
    // possible nodes
    if ((current->val) < val) {
      before[currentLevel - 1] = current;
    }

    // move one level down if it wil hit a node larger than the intended value
    // or a "null pointer" node
    if ((current->next)[currentLevel - 1]->isNullPtr) {
      currentLevel = currentLevel - 1;
    } else if ((current->next)[currentLevel - 1]->val >= val) {
      currentLevel = currentLevel - 1;
    } else {
      // move across if there are no complications
      current = (current->next)[currentLevel - 1];
    }
  }

  return before;
}

// check if there exists a node that contains a certain number
bool SkipList::contains(int val) const {
  int currentLevel = levels; // current level to be iterated through
  SNode *current = head;     // iterating current node

  // // iterate through the levels, starting with the topmost
  while (currentLevel > 0) {
    // move one level down if it wil hit a node larger than the intended value
    // or a "null pointer" node
    if ((current->next)[currentLevel - 1]->isNullPtr) {
      currentLevel = currentLevel - 1;
    } else if ((current->next)[currentLevel - 1]->val > val) {
      currentLevel = currentLevel - 1;
    }
    // if the node is found, return true
    else if ((current->next)[currentLevel - 1]->val == val) {
      return true;
    } else {
      // move across if there are no complications
      current = (current->next)[currentLevel - 1];
    }
  }

  return false;
}

// remove the fist found node with a certain number, returning true if the
// operation was successfull
bool SkipList::remove(int val) {
  vector<SNode *> before =
      getBeforeNodes(val);      // vector of nodes that will
                                // remove its link to the removed node
  SNode *deleteSNode = nullptr; // removed node to be deleted

  // check if there is a node containing the value
  if (!(contains(val))) {
    return false;
  }

  // go through the nodes, changing their link
  for (int i = levels; i > 0; i--) {
    // check if the node links to the removed node
    if (!((before[i - 1]->next)[i - 1]->isNullPtr) &&
        ((before[i - 1]->next)[i - 1]->val) == val) {

      // get the node that the removed node is linked to
      SNode *skip = (((before[i - 1]->next)[i - 1])->next)[i - 1];

      // mark the removed node as to be deleted
      deleteSNode = (before[i - 1]->next)[i - 1];

      // link the previous and next nodes together
      (before[i - 1]->next)[i - 1] = skip;
    }
  }

  // delete nodes later
  for (SNode *toBeDeleted : deleteSNode->next) {
    deleteSNodes.insert(toBeDeleted);
  }

  delete deleteSNode; // delete the removed node

  return true;
}
