/**
 * @file mainPart1.cpp
 * 
 * AdventOfCode
 * 
 * @author MivojBlazek
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool isVisibleFormLeft(int row, int col, int trees[99][99])
{
    for (int i = 0; i < col; i++)
    {
        if (trees[row][i] >= trees[row][col])
        {
            return false;
        }
    }
    return true;
}

bool isVisibleFromRight(int row, int col, int trees[99][99])
{
    for (int i = col + 1; i < 99; i++)
    {
        if (trees[row][i] >= trees[row][col])
        {
            return false;
        }
    }
    return true;
}

bool isVisibleFromTop(int row, int col, int trees[99][99])
{
    for (int i = 0; i < row; i++)
    {
        if (trees[i][col] >= trees[row][col])
        {
            return false;
        }
    }
    return true;
}

bool isVisibleFromBottom(int row, int col, int trees[99][99])
{
    for (int i = row + 1; i < 99; i++)
    {
        if (trees[i][col] >= trees[row][col])
        {
            return false;
        }
    }
    return true;
}

bool isTreeVisible(int row, int col, int trees[99][99])
{
    if (row == 0 || row == 98 || col == 0 || col == 98)
    {
        return true;
    }

    return isVisibleFormLeft(row, col, trees) || isVisibleFromRight(row, col, trees)
        || isVisibleFromTop(row, col, trees) || isVisibleFromBottom(row, col, trees);
}

int main()
{
    ifstream inputFile("input.in");
    if (!inputFile.is_open())
    {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    string line;
    int trees[99][99] = {0};

    // Load data to 2D array
    for (int row = 0; row < 99; row++)
    {
        for (int col = 0; col < 99; col++)
        {
            char character;
            inputFile.get(character);
            while (character == '\r' || character == '\n' || character == '\0')
            {
                inputFile.get(character);
                if (inputFile.eof())
                {
                    break;
                }
            }
            trees[row][col] = character - '0';
        }
    }
    inputFile.close();

    // Compute visible trees
    int count = 0;
    for (int row = 0; row < 99; row++)
    {
        for (int col = 0; col < 99; col++)
        {
            if (isTreeVisible(row, col, trees))
            {
                count++;
                cout << "*";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }

    cout << "Number of visible trees: " << count << endl;
    return 0;
}
