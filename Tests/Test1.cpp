//============================================================================
// Name        : Test1
// Test Desc.  : <desc>
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/skiplist.h"
#include "applib/random.h"

#include <iostream>
#include <sstream>

using namespace std;

TEST(Test1, t1)
{


	// Maze myMaze;
    // string mazeFile = "data/maze0.txt";
    // bool result = false;
    // result = myMaze.load(mazeFile);
    // if (! result)
    // {
    //     cerr << "Failed to load " << mazeFile << endl;
    //     //rest of this is useless without the test file being loaded in, so exit here...
    //     ASSERT_TRUE(result); 
    //     return;
    // }
    // //if made it here, should pass.
    // EXPECT_TRUE(result); 

    // cout << "*** Solving " << mazeFile << endl;
    // result = myMaze.solve();
    // if (result)
    // {
    //     EXPECT_TRUE(result);
    //     cout << "Path: " << myMaze.getPath() << endl;
    // }
    // else
    // {
    //     //should fail here... b/c solve() failed to solve it.
    //     EXPECT_TRUE(result);
    //     cout << "Failed to solve: " << mazeFile << endl;
    // }
    // cout << myMaze << endl;
    // string expectedPath;
    // //solving order of: N E S W... (with backtracking)
    // expectedPath = "NNNNNESSSSENNNNESSSSENNNNESSSSENNNNN";
    // EXPECT_EQ(myMaze.getPath(), expectedPath);
}
