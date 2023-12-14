//============================================================================
// Name        : Test3
// Test Desc.  : testing SkipList with multiple levels
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/skiplist.h"
#include "applib/random.h"

#include <iostream>
#include <sstream>

using namespace std;

//testing SkipList with multiple levels
TEST(Test3, multiLevelSkiplist)
{

	// stringstream outSS;
  // SkipList skp(3, 80);
  // skp.add(vector<int>{9, 1, 7, 5, 3, 20});

  // outSS << skp;
  // assert(outSS.str() == "[level: 3] 7-->nullptr\n"
  //                       "[level: 2] 3-->7-->nullptr\n"
  //                       "[level: 1] 1-->3-->5-->7-->9-->20-->nullptr\n");

  // skp.add(vector<int>{-20, 100});
  // outSS.str("");
  // outSS << skp;
  // assert(outSS.str() ==
  //        "[level: 3] -20-->7-->100-->nullptr\n"
  //        "[level: 2] -20-->3-->7-->100-->nullptr\n"
  //        "[level: 1] -20-->1-->3-->5-->7-->9-->20-->100-->nullptr\n");

  // // TODO(student) check that contains searches from top level down
  // assert(skp.contains(1) && skp.contains(7) && skp.contains(9));
  // assert(!skp.contains(0) && !skp.contains(200));
  // assert(skp.contains(-20) && skp.contains(100));

  // SkipList skp2(3, 30);
  // skp2.add(vector<int>{9, 1, 7, 5, 3, 20});
  // outSS.str("");
  // outSS << skp2;
  // assert(outSS.str() == "[level: 3] nullptr\n"
  //                       "[level: 2] 3-->5-->nullptr\n"
  //                       "[level: 1] 1-->3-->5-->7-->9-->20-->nullptr\n");

  // assert(skp2.contains(3) && skp2.contains(5) && skp2.contains(20));
  // assert(!skp2.contains(-3) && !skp2.contains(4) && !skp2.contains(200));
  // // TODO(student) check there are no memory leaks after test completed
  // cout << "test3 done." << endl;
}

