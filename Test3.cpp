//============================================================================
// Name        : Test3
// Test Desc.  : testing SkipList with multiple levels
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

// testing SkipList with multiple levels
TEST(Test3, multiLevelSkiplist)
{
	Random r;
	r.setSeed(0);


	stringstream outSS;
	SkipList skplst(3, 80);
	skplst.add(vector<int>{9, 1, 7, 5, 3, 20});

	outSS << skplst;
	string ansStr = "[level: 3] 7-->nullptr\n"
					"[level: 2] 3-->7-->nullptr\n"
					"[level: 1] 1-->3-->5-->7-->9-->20-->nullptr\n";
	EXPECT_EQ(outSS.str(), ansStr);

	skplst.add(vector<int>{-20, 100});
	outSS.str("");
	outSS << skplst;
	ansStr = "[level: 3] -20-->7-->100-->nullptr\n"
			 "[level: 2] -20-->3-->7-->100-->nullptr\n"
			 "[level: 1] -20-->1-->3-->5-->7-->9-->20-->100-->nullptr\n";
	EXPECT_EQ(outSS.str(), ansStr);

	// // TODO(student) check that contains searches from top level down
	EXPECT_TRUE(skplst.contains(1) && skplst.contains(7) && skplst.contains(9));
	EXPECT_TRUE(!skplst.contains(0) && !skplst.contains(200));
	EXPECT_TRUE(skplst.contains(-20) && skplst.contains(100));

	SkipList skplst2(3, 30);
	skplst2.add(vector<int>{9, 1, 7, 5, 3, 20});
	outSS.str("");
	outSS << skplst2;
	ansStr = "[level: 3] nullptr\n"
	         "[level: 2] 3-->5-->nullptr\n"
	         "[level: 1] 1-->3-->5-->7-->9-->20-->nullptr\n";
	EXPECT_EQ(outSS.str(), ansStr);

	EXPECT_TRUE(skplst2.contains(3) && skplst2.contains(5) && skplst2.contains(20));
	EXPECT_TRUE(!skplst2.contains(-3) && !skplst2.contains(4) && !skplst2.contains(200));


	cout << "Seed is: " << r.getSeed() << endl;
	//memory leaks are covered by valgrind within gTest. 
	// So if you have mem leaks, GitHub will be informed, the test will fail.
}
