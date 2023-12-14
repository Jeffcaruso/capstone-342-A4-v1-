//============================================================================
// Name        : Test4
// Test Desc.  : removing from multi-level SkipList
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/skiplist.h"
#include "applib/random.h"

#include <iostream>
#include <sstream>

using namespace std;


// removing from multi-level SkipList
TEST(Test4, removeFromMultiLevelSkiplist)
{

	// stringstream outSS;
  // SkipList skp(3, 50);
  // skp.add(vector<int>{9, 1, 7, 5, 3, 20});

  // outSS << skp;
  // assert(outSS.str() == "[level: 3] 20-->nullptr\n"
  //                       "[level: 2] 3-->5-->7-->9-->20-->nullptr\n"
  //                       "[level: 1] 1-->3-->5-->7-->9-->20-->nullptr\n");
  // SkipList skp2(skp);
  // assert(skp.remove(1));
  // assert(!skp.remove(100));
  // assert(skp.remove(9));

  // outSS.str("");
  // outSS << skp;
  // assert(outSS.str() == "[level: 3] 20-->nullptr\n"
  //                       "[level: 2] 3-->5-->7-->20-->nullptr\n"
  //                       "[level: 1] 3-->5-->7-->20-->nullptr\n");

  // // skp2 should be unchanged
  // outSS.str("");
  // outSS << skp2;
  // assert(outSS.str() == "[level: 3] 20-->nullptr\n"
  //                       "[level: 2] 3-->5-->7-->9-->20-->nullptr\n"
  //                       "[level: 1] 1-->3-->5-->7-->9-->20-->nullptr\n");
  // // TODO(student) check there are no memory leaks after test completed
  // cout << "test4 done." << endl;
}
