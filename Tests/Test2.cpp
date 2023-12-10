//============================================================================
// Name        : Test2
// Test Desc.  : <desc>
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/maze.h"

#include <iostream>
#include <sstream>

using namespace std;

//note / reminder:
// use EXPECT_EQ (or _NE) for std::string
// for c strings, use EXPECT_STREQ (or STRNE)
// http://google.github.io/googletest/reference/assertions.html

TEST(Test2, maze1)
{
	Maze myMaze;
    string mazeFile = "data/maze1.txt";
    bool result = false;
    result = myMaze.load(mazeFile);
    if (! result)
    {
        cerr << "Failed to load " << mazeFile << endl;
        //rest of this is useless without the test file being loaded in, so exit here...
        ASSERT_TRUE(result); 
        return;
    }
    //if made it here, should pass.
    EXPECT_TRUE(result); 

    cout << "*** Solving " << mazeFile << endl;
    result = myMaze.solve();
    if (result)
    {
        EXPECT_TRUE(result);
        cout << "Path: " << myMaze.getPath() << endl;
    }
    else
    {
        //should fail here... b/c solve() failed to solve it.
        EXPECT_TRUE(result);
        cout << "Failed to solve: " << mazeFile << endl;
    }
    cout << myMaze << endl;
    string expectedPath;
    //solving order of: N E S W... (with backtracking)
    expectedPath = "NNWWWWWNNNEEEEEESEESSSEEENNNNN";
    EXPECT_EQ(myMaze.getPath(), expectedPath);

}

