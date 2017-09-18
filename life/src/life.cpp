#include <iostream>
#include <string>
#include "grid.h"
#include "lifeutil.h"
#include <fstream>
#include <set>
using namespace std;

/*
*André Palm, andpa149
*Elise Lång elila090
*
*
* This file emulates Conway's Game of Life.
* It takes a textfile and uses it as input for the 
* initial setup of the Game of Life Board.
*
*/


void welcomeMsg()
// Prints out the welcome message with rules on the display.
{
  cout <<   " Welcome to the TDDD86 Game of Life,"
            "\n a simulation of the lifecycle of a bacteria colony."
            "\n Cells (X)live and die by the following rules:\n  "
            " - A cell with 1 or fewer neighbours dies.\n  "
            " - Locations with 2 neighbours remain stable.\n "
            "  - Locations with 3 neighbours will create life.\n "
            "  - A cell with 4 or more neighbours dies.\n" << endl;
}

void displayGrid(Grid<char> grid)
// Takes current grind as input and prints it out.
{
    for (int i = 0; i < grid.numRows(); i++) {
        for (int j = 0; j < grid.numCols(); j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

int countNeigh(int row, int col, Grid<char> grid)
// Counts the numbers of neighbours of the given cell.
{
    int numRow = grid.numRows();
    int numCol = grid.numCols();
    int count = 0;

    set<int> Dx, Dy;

    if (row != 0)
    {
        Dx.insert(-1);
    }
    if (col != 0)
    {
        Dy.insert(-1);
    }
    if (row != numRow - 1)
    {
        Dx.insert(1);
    }
    if (col != numCol - 1)
    {
        Dy.insert(1);
    }

    Dx.insert(0);
    Dy.insert(0);


    for (set<int>::iterator dx = Dx.begin(); dx != Dx.end(); dx++)
    {
        for (set<int>::iterator dy = Dy.begin(); dy != Dy.end(); dy++)
        {
            if ( !(*dx == 0 && *dy == 0) && grid[row + *dx][col + *dy] == 'X' )
            {
                count++;
            }
        }
    }

    return count;
}

void nextGeneration(Grid<char>& oldGrid)
// Iterate the grid according to the rules of Game of Life.
{
    int row = oldGrid.numRows();
    int col = oldGrid.numCols();
    Grid<char> newGrid = Grid<char>(row, col); 

    for(int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int count = countNeigh(i, j, oldGrid);
            if (count == 2) {
                newGrid[i][j] = oldGrid[i][j];
            } else if (count == 3) {
                newGrid[i][j] = 'X';
            } else {
                newGrid[i][j] = '-';
            }
        }
    }
    oldGrid = newGrid;
}

Grid<char> getTextFile()
// Prompts for filename and creates a grid from it.
{
    ifstream inFile;
    string fileName;
    cout << "Grid input file name? ";
    cin >> fileName;
    inFile.open(fileName);

    int row, col;
    string buf;
    inFile >> buf;
    row = atoi(buf.c_str());

    inFile >> buf;
    col = atoi(buf.c_str());

    Grid<char> grid = Grid<char>(row, col);

    string charRow;
    for (int i=0; i<row; i++) {
        inFile >> charRow;
        for (int j=0; j<col; j++) {
            grid[i][j] = charRow[j];
        }
    }

    inFile.close();

    return grid;
}

int main()
// Starts the main menu.
{
    welcomeMsg();
    Grid<char> grid;
    grid = getTextFile();
    
    char option = '0'; // 
    while (option != 'q')
    {
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> option;
        if (option == 't') {
            clearConsole();
            nextGeneration(grid);
            displayGrid(grid);
        } else if (option == 'a') {
            int iterations;
            cin >> iterations;
            for (int i = 0; i < iterations; i++) {
                clearConsole();
                nextGeneration(grid);
                displayGrid(grid);
                pause(100);
            }
        }
    }

    cout << "Have a nice Life!" << endl;
    return 0;
}

