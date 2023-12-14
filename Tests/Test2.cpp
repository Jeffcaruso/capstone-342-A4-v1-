//============================================================================
// Name        : Test2
// Test Desc.  : testing the copy constructor for the SkipList
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/skiplist.h"
#include "applib/random.h"

#include <iostream>
#include <sstream>

using namespace std;

//note / reminder:
// use EXPECT_EQ (or _NE) for std::string
// for c strings, use EXPECT_STREQ (or STRNE)
// http://google.github.io/googletest/reference/assertions.html

// testing the copy constructor for the SkipList
TEST(Test2, copyConstructorTesting)
{

	// stringstream outSS;
  // SkipList *skp1 = new SkipList;
  // skp1->add(vector<int>{9, 1, 7, 5});

  // outSS.str("");
  // outSS << *skp1;
  // assert(outSS.str() == "[level: 1] 1-->5-->7-->9-->nullptr\n");

  // SkipList *skp2 = new SkipList(*skp1);
  // delete skp1;
  // outSS.str("");
  // outSS << *skp2;
  // assert(outSS.str() == "[level: 1] 1-->5-->7-->9-->nullptr\n");
  // delete skp2;
  // // TODO(student) check there are no memory leaks after test completed
  // cout << "test2 done." << endl;
}

