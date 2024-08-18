/**
 * @file mainPart2.cpp
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

int numberOfVisibleTreesOnLeft(int row, int col, int trees[99][99])
{
    int count = 0;
    for (int i = col - 1; i >= 0; i--)
    {
        count++;
        if (trees[row][i] >= trees[row][col])
        {
            return count;
        }
    }
    return count;
}

int numberOfVisibleTreesOnRight(int row, int col, int trees[99][99])
{
    int count = 0;
    for (int i = col + 1; i < 99; i++)
    {
        count++;
        if (trees[row][i] >= trees[row][col])
        {
            return count;
        }
    }
    return count;
}

int numberOfVisibleTreesOnTop(int row, int col, int trees[99][99])
{
    int count = 0;
    for (int i = row - 1; i >= 0; i--)
    {
        count++;
        if (trees[i][col] >= trees[row][col])
        {
            return count;
        }
    }
    return count;
}

int numberOfVisibleTreesOnBottom(int row, int col, int trees[99][99])
{
    int count = 0;
    for (int i = row + 1; i < 99; i++)
    {
        count++;
        if (trees[i][col] >= trees[row][col])
        {
            return count;
        }
    }
    return count;
}

int numberOfVisibleTrees(int row, int col, int trees[99][99])
{
    return numberOfVisibleTreesOnLeft(row, col, trees) * numberOfVisibleTreesOnRight(row, col, trees)
        * numberOfVisibleTreesOnTop(row, col, trees) * numberOfVisibleTreesOnBottom(row, col, trees);
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
    int maxScore = 0;
    for (int row = 0; row < 99; row++)
    {
        for (int col = 0; col < 99; col++)
        {
            int score = numberOfVisibleTrees(row, col, trees);
            if (score > maxScore)
            {
                maxScore = score;
            }
        }
    }

    cout << "Highest possible scenic score: " << maxScore << endl;
    return 0;
}
