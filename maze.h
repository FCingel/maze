#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

const int MAX = 100;

struct Location
{
    friend std::ostream &operator <<(std::ostream &os, const Location &location)
    {
        os << "(" << location.x << ", " << location.y << ")";
        return os;
    }
    bool operator ==(const Location &rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
    bool operator !=(const Location &rhs) const
    {
        return !(*this == rhs);
    }
    operator bool() const
    {
        return x >= 0;
    }
    Location(int x=-1, int y=-1) : x(x), y(y) {}
    int x, y;
};

class Maze
{
private:
    Location start, finish;
    int row, column, xStart, yStart, xFinish, yFinish, xCurrent, yCurrent;
    char mazeArray[MAX][MAX];     //I'm convinced vector of vector is pure evil
    bool wasHere[MAX][MAX];
    fstream infile;

    stack<int> xVal;
    stack<int> yVal;

public:
    void load();
    void print();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    bool solve();
};

#endif
