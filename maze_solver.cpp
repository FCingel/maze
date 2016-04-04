/*
Frank Cingel
Maze
*/

#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>

#include "maze.h"
#include "maze.cpp"

using namespace std;

main()
{
    Maze maze;

    maze.load();
    maze.solve();
    maze.print();

    cout << endl;
}



