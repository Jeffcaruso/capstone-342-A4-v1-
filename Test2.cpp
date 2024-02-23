//============================================================================
// Name        : Test2
// Test Desc.  : testing the copy constructor for the SkipList
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

// note / reminder:
//  use EXPECT_EQ (or _NE) for std::string
//  for c strings, use EXPECT_STREQ (or STRNE)
//  http://google.github.io/googletest/reference/assertions.html

// testing the copy constructor for the SkipList
TEST(Test2, copyConstructorTesting)
{
	Random r;
	r.setSeed(0);


	stringstream outSS;
	SkipList *Skplst1 = new SkipList;
	Skplst1->add(vector<int>{9, 1, 7, 5});

	outSS.str("");
	outSS << *Skplst1;
	string ansStr = "[level: 1] 1-->5-->7-->9-->nullptr\n";
	EXPECT_EQ(outSS.str(), ansStr);

	SkipList *skplst2 = new SkipList(*Skplst1);
	delete Skplst1;
	outSS.str("");
	outSS << *skplst2;
	ansStr = "[level: 1] 1-->5-->7-->9-->nullptr\n";
	EXPECT_EQ(outSS.str(), ansStr);
	delete skplst2;

	cout << "Seed is: " << r.getSeed() << endl;

	//memory leaks are covered by valgrind within gTest. 
	// So if you have mem leaks, GitHub will be informed, the test will fail.
}
