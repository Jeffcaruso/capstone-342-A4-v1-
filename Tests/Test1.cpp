//============================================================================
// Name        : Test1
// Test Desc.  : testing basic operations: operator<<, add, contains
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/skiplist.h"
#include "applib/random.h"

#include <iostream>
#include <sstream>

using namespace std;


// testing basic operations: operator<<, add, contains
TEST(Test1, testingOutAddContains)
{


	// stringstream outSS;
  // SkipList skp;
  // skp.add(3);
  // outSS << skp;
  // assert(outSS.str() == "[level: 1] 3-->nullptr\n");

  // skp.add(9);
  // outSS.str("");
  // outSS << skp;
  // assert(outSS.str() == "[level: 1] 3-->9-->nullptr\n");

  // skp.add(1);
  // outSS.str("");
  // outSS << skp;
  // assert(outSS.str() == "[level: 1] 1-->3-->9-->nullptr\n");

  // skp.add(vector<int>{7, 5});
  // outSS.str("");
  // outSS << skp;
  // assert(outSS.str() == "[level: 1] 1-->3-->5-->7-->9-->nullptr\n");

  // assert(skp.contains(1) && skp.contains(7) && skp.contains(9));
  // assert(!skp.contains(0) && !skp.contains(20));

  // // TODO(student) check there are no memory leaks after test completed
  // cout << "test1 done." << endl;
}
