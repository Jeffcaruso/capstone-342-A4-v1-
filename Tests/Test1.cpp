//============================================================================
// Name        : Test1
// Test Desc.  : testing basic operations: operator<<, add, contains for SkipList
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//==========================================================n==================

#include <gtest/gtest.h>
#include "applib/skiplist.h"
#include "applib/random.h"

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// testing basic operations: operator<<, add, contains
TEST(Test1, testingOutAddContains)
{
	stringstream outSS;
	SkipList skplst;
	skplst.add(3);
	outSS << skplst;
	string ansStr ="[level: 1] 3-->nullptr\n";
	EXPECT_EQ(outSS.str(), ansStr);

	skplst.add(9);
	outSS.str("");
	outSS << skplst;
	ansStr = "[level: 1] 3-->9-->nullptr\n";
	EXPECT_EQ(outSS.str(), ansStr);

	skplst.add(1);
	outSS.str("");
	outSS << skplst;
	ansStr = "[level: 1] 1-->3-->9-->nullptr\n";
	EXPECT_EQ(outSS.str(), ansStr);

	skplst.add(vector<int>{7, 5});
	outSS.str("");
	outSS << skplst;
	ansStr = "[level: 1] 1-->3-->5-->7-->9-->nullptr\n";
	EXPECT_EQ(outSS.str(), ansStr);

	EXPECT_TRUE(skplst.contains(1) && skplst.contains(7) && skplst.contains(9));
	EXPECT_TRUE(!skplst.contains(0) && !skplst.contains(20));


	// // TODO(student) check there are no memory leaks after test completed*
	// cout << "test1 done." << endl;
	//memory leaks are covered by valgrind within gTest. 
	// So if you have mem leaks, GitHub will be informed, the test will fail.


}
