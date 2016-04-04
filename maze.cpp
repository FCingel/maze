#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>

#include "maze.h"

using namespace std;

void Maze::load()
{
    string mazeFileName, line;
    int rowCount = 0, length = 0, xPath, yPath;

    cout << "Enter Maze File: ";
    cin >> mazeFileName;

    infile.open(mazeFileName.c_str());
    if (!infile.is_open())
    {
        cout << "ERROR: Could not open file" << endl;
        exit (1);
    }

    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
        {
            mazeArray[i][j] = 'F';
            wasHere[i][j] = false;
        }

    getline(infile, line);
    length = line.size();

    while (infile)
    {
        for (int i = 0; i < length; i++)
        {
            if(line[i] == '*')
            {
                xPath = i;
                yPath = rowCount;
                mazeArray[yPath][xPath] = 'T';
            }
            else if(line[i] == 'S')
            {
                xStart = i;
                yStart = rowCount;
            }
            else if(line[i] == 'F')
            {
                xFinish = i;
                yFinish = rowCount;
            }
        }
        cout << line << endl;

        getline (infile, line);
        rowCount++;
    }

    Location start(xStart, yStart);
    cout << "Start is at " << start << endl;

    Location finish(xFinish, yFinish);
    cout << "Finish is at " << finish << endl << endl;

    mazeArray[yStart][xStart] = 'T';
    mazeArray[yFinish][xFinish] = 'T';

    row = rowCount - 2;
    column = length - 2;

    infile.close();
    infile.clear();
}


void Maze::print()
{
    cout << "+";
    for(int i = 0; i <= column-1; i++)
    {
        cout << "-";
    }
    cout << "+";

    for(int i = 1; i <= row; i++)
    {
        cout <<  endl << "|";
        for(int j = 1; j <= column; j++)
        {
            if(i == yCurrent && j == xCurrent)
                cout << "O";
            else if(wasHere[i][j] == true)
                cout << "*";
            else if(wasHere[i][j] == false)
                cout << " ";
        }
        cout << "|";
    }

    cout << endl << "+";
    for(int i = 0; i <= column-1; i++)
    {
        cout << "-";
    }
    cout << "+" << endl << endl;
}


void Maze::moveLeft()
{
    mazeArray[yCurrent][xCurrent] = 'F';
    wasHere[yCurrent][xCurrent] = true;

    if(xCurrent == xFinish && yCurrent == yFinish)
        return;

    while(mazeArray[yCurrent][xCurrent-1] == 'T')
    {
        if(mazeArray[yCurrent-1][xCurrent] == 'T')
        {
            xVal.push(xCurrent);
            yVal.push(yCurrent-1);
        }
        if(mazeArray[yCurrent+1][xCurrent] == 'T')
        {
            yVal.push(yCurrent+1);
            xVal.push(xCurrent);
        }
        xCurrent--;

        mazeArray[yCurrent][xCurrent] = 'F';
        wasHere[yCurrent][xCurrent] = true;

        cout << " *LEFT* " << endl;
        print();


        if(yCurrent == yFinish && xCurrent == xFinish)
            return;
    }

    if(mazeArray[yCurrent][xCurrent-1] == 'F' && mazeArray[yCurrent+1][xCurrent] == 'F'
            && mazeArray[yCurrent-1][xCurrent] == 'F' && mazeArray[yCurrent][xCurrent+1] == 'F')
    {
        cout << " *Dead end* " << endl;

        xCurrent = xVal.top();
        yCurrent = yVal.top()+1;
        xVal.pop();
        yVal.pop();

    }
    if(mazeArray[yCurrent][xCurrent-1] == 'F' && mazeArray[yCurrent-1][xCurrent] == 'F')
    {
        moveDown();
    }
    if(mazeArray[yCurrent][xCurrent-1] == 'F' && mazeArray[yCurrent+1][xCurrent] == 'F')
    {
        moveUp();
    }
    if(mazeArray[yCurrent-1][xCurrent] == 'T')
    {
        yVal.push(yCurrent-1);
        xVal.push(xCurrent);
        moveDown();
    }
}


void Maze::moveRight()
{
    mazeArray[yCurrent][xCurrent] = 'F';
    wasHere[yCurrent][xCurrent] = true;

    if(xCurrent == xFinish && yCurrent == yFinish)
        return;

    while(mazeArray[yCurrent][xCurrent+1] == 'T')
    {
        if(mazeArray[yCurrent-1][xCurrent] == 'T')
        {
            yVal.push(yCurrent-1);
            xVal.push(xCurrent);
        }
        if(mazeArray[yCurrent+1][xCurrent] == 'T')
        {
            yVal.push(yCurrent+1);
            xVal.push(xCurrent);
        }
        xCurrent++;

        mazeArray[yCurrent][xCurrent] = 'F';
        wasHere[yCurrent][xCurrent] = true;

        cout << " *RIGHT* " << endl;
        print();

        if(yCurrent == yFinish && xCurrent == xFinish)
            return;
    }

    if(mazeArray[yCurrent][xCurrent-1] == 'F' && mazeArray[yCurrent+1][xCurrent] == 'F'
            && mazeArray[yCurrent-1][xCurrent] == 'F' && mazeArray[yCurrent][xCurrent+1] == 'F')
    {
        cout << " *Dead end* " << endl;

        xCurrent = xVal.top();
        yCurrent = yVal.top();
        xVal.pop();
        yVal.pop();
    }

    if(mazeArray[yCurrent][xCurrent+1] == 'F' && mazeArray[yCurrent-1][xCurrent] == 'F')
    {
        moveDown();
    }
    if(mazeArray[yCurrent][xCurrent+1] == 'F' && mazeArray[yCurrent+1][xCurrent] == 'F')
    {
        moveUp();
    }
    if(mazeArray[yCurrent-1][xCurrent] == 'T')
    {
        xVal.push(xCurrent);
        yVal.push(yCurrent-1);

        moveDown();
    }
}


void Maze::moveUp()
{
    mazeArray[yCurrent][xCurrent] = 'F';
    wasHere[yCurrent][xCurrent] = true;

    if(xCurrent == xFinish && yCurrent == yFinish)
        return;

    while(mazeArray[yCurrent-1][xCurrent] == 'T')
    {
        if(mazeArray[yCurrent][xCurrent+1] == 'T')
        {
            xVal.push(xCurrent+1);
            yVal.push(yCurrent);
        }
        if(mazeArray[yCurrent][xCurrent-1] == 'T')
        {
            xVal.push(xCurrent-1);
            yVal.push(yCurrent);
        }
        yCurrent--;

        mazeArray[yCurrent][xCurrent] = 'F';
        wasHere[yCurrent][xCurrent] = true;

        cout << " *UP* " << endl;

        print();

        if(yCurrent == yFinish && xCurrent == xFinish)
            return;
    }

    if(mazeArray[yCurrent-1][xCurrent] == 'F' && mazeArray[yCurrent][xCurrent+1] == 'F'
            && mazeArray[yCurrent][xCurrent-1] == 'F' && mazeArray[yCurrent+1][xCurrent] == 'F')
    {
        cout << " *Dead end* " << endl;

        xCurrent = xVal.top();
        yCurrent = yVal.top();
        xVal.pop();
        yVal.pop();
    }
    if(mazeArray[yCurrent-1][xCurrent] == 'F' && mazeArray[yCurrent][xCurrent+1] == 'F')
    {
        moveLeft();
    }
    if(mazeArray[yCurrent-1][xCurrent] == 'F' && mazeArray[yCurrent][xCurrent-1] == 'F')
    {
        moveRight();
    }
    if(mazeArray[yCurrent][xCurrent-1] == 'T' && mazeArray[yCurrent][xCurrent+1] == 'T')
    {
        xVal.push(xCurrent-1);
        yVal.push(yCurrent);

        moveRight();
    }
}


void Maze::moveDown()
{
    mazeArray[yCurrent][xCurrent] = 'F';
    wasHere[yCurrent][xCurrent] = true;

    if(xCurrent == xFinish && yCurrent == yFinish)
        return;

    while(mazeArray[yCurrent+1][xCurrent] == 'T')
    {
        if(mazeArray[yCurrent][xCurrent+1] == 'T')
        {
            xVal.push(xCurrent+1);
            yVal.push(yCurrent);
        }
        if(mazeArray[yCurrent][xCurrent-1] == 'T')
        {
            xVal.push(xCurrent-1);
            yVal.push(yCurrent);
        }
        yCurrent++;

        mazeArray[yCurrent][xCurrent] = 'F';
        wasHere[yCurrent][xCurrent] = true;


        cout << " *DOWN* " << endl;

        print();

        if(yCurrent == yFinish && xCurrent == xFinish)
            return;
    }

    if(mazeArray[yCurrent+1][xCurrent] == 'F' && mazeArray[yCurrent][xCurrent+1] == 'F' && mazeArray[yCurrent][xCurrent-1] == 'F' && mazeArray[yCurrent-1][xCurrent] == 'F')
    {
        cout << " *Dead end* " << endl;

        xCurrent = xVal.top();
        yCurrent = yVal.top();
        xVal.pop();
        yVal.pop();
    }
    if(mazeArray[yCurrent+1][xCurrent] == 'F' && mazeArray[yCurrent][xCurrent+1] == 'F')
    {
        moveLeft();
    }
    if(mazeArray[yCurrent+1][xCurrent] == 'F' && mazeArray[yCurrent][xCurrent-1] == 'F')
    {
        moveRight();
    }
    if(mazeArray[yCurrent][xCurrent-1] == 'T' && mazeArray[yCurrent][xCurrent+1] == 'T')
    {
        xVal.push(xCurrent-1);
        yVal.push(yCurrent);

        moveRight();
    }
}


bool Maze::solve()
{
    xCurrent = xStart;
    yCurrent = yStart;

    if (mazeArray[yCurrent][xCurrent+1] == 'F' && mazeArray[yCurrent+1][xCurrent] == 'F'
            && mazeArray[yCurrent-1][xCurrent] == 'F')
        moveLeft();

    if (mazeArray[yCurrent][xCurrent-1] == 'F' && mazeArray[yCurrent+1][xCurrent] == 'F'
            && mazeArray[yCurrent-1][xCurrent] == 'F')
        moveRight();

    if (mazeArray[yCurrent+1][xCurrent] == 'F' && mazeArray[yCurrent][xCurrent+1] == 'F'
            && mazeArray[yCurrent][xCurrent-1] == 'F')
        moveUp();

    if (mazeArray[yCurrent-1][xCurrent] == 'F' && mazeArray[yCurrent][xCurrent+1] == 'F'
            && mazeArray[yCurrent][xCurrent-1] == 'F')
        moveDown();

    if(yCurrent == yFinish && xCurrent == xFinish)
    {
        cout << "MAZE SOLVED" << endl;

        return true;
    }
}
