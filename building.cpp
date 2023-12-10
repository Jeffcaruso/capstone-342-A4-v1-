#include "applib/maze.h" 

#include <iostream>


int main()
{
    Maze myMaze;

    //don't need to loop through tests. That coverage is being done by gTest.
    //can loop through one tho...

    string mazeFile = "data/maze0.txt";
    if (!myMaze.load(mazeFile))
    {
        cerr << "Failed to load " << mazeFile << endl;
        return -1;
    }
    cout << "*** Solving " << mazeFile << endl;
    if (myMaze.solve())
    {
        cout << "Path: " << myMaze.getPath() << endl;
    }
    else
    {
        cout << "Failed to solve: " << mazeFile << endl;
    }
    cout << myMaze << endl;
}

