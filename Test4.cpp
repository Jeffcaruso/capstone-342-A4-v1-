//============================================================================
// Name        : Test4
// Test Desc.  : removing from multi-level SkipList
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "skiplist.h"
#include "random.h"

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// removing from multi-level SkipList
TEST(Test4, removeFromMultiLevelSkiplist)
{
	stringstream outSS;
	SkipList skplst(3, 50);
	skplst.add(vector<int>{9, 1, 7, 5, 3, 20});
	outSS << skplst;
	string ansStr = "[level: 3] 20-->nullptr\n"
					"[level: 2] 3-->5-->7-->9-->20-->nullptr\n"
					"[level: 1] 1-->3-->5-->7-->9-->20-->nullptr\n";
	EXPECT_EQ(outSS.str(), ansStr);

	SkipList skplst2(skplst);
	ASSERT_TRUE(skplst.remove(1));
	ASSERT_TRUE(!skplst.remove(100));
	ASSERT_TRUE(skplst.remove(9));

	outSS.str("");
	outSS << skplst;
	ansStr = "[level: 3] 20-->nullptr\n"
			 "[level: 2] 3-->5-->7-->20-->nullptr\n"
			 "[level: 1] 3-->5-->7-->20-->nullptr\n";

	// // skp2 should be unchanged
	outSS.str("");
	outSS << skplst2;
	ansStr = "[level: 3] 20-->nullptr\n"
			 "[level: 2] 3-->5-->7-->9-->20-->nullptr\n"
			 "[level: 1] 1-->3-->5-->7-->9-->20-->nullptr\n";
	EXPECT_EQ(outSS.str(), ansStr);

	//memory leaks are covered by valgrind within gTest. 
	// So if you have mem leaks, GitHub will be informed, the test will fail.
}
