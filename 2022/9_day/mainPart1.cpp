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
#include <set>
#include <utility>

using namespace std;

int main()
{
    ifstream inputFile("input.in");
    if (!inputFile.is_open())
    {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    pair<int, int> head = {0, 0};
    pair<int, int> tail = {0, 0};
    set<pair<int, int>> visited;
    visited.insert(tail);

    string direction;
    int steps;
    while (inputFile >> direction >> steps)
    {
        for (int i = 0; i < steps; i++)
        {
            // Move head
            if (direction == "R")
            {
                head.first += 1;
            }
            else if (direction == "L")
            {
                head.first -= 1;
            }
            else if (direction == "U")
            {
                head.second += 1;
            }
            else if (direction == "D")
            {
                head.second -= 1;
            }

            // Move tail
            if (abs(head.first - tail.first) > 1 || abs(head.second - tail.second) > 1)
            {
                // Move tail diagonally
                if (head.first != tail.first && head.second != tail.second)
                {
                    // X-axis move
                    if (head.first > tail.first)
                    {
                        tail.first++;
                    }
                    else
                    {
                        tail.first--;
                    }

                    // Y-axis move
                    if (head.second > tail.second)
                    {
                        tail.second++;
                    }
                    else
                    {
                        tail.second--;
                    }
                }
                else if (head.first != tail.first)
                {
                    // Move tail to the head on x-axis
                    if (head.first > tail.first)
                    {
                        tail.first++;
                    }
                    else
                    {
                        tail.first--;
                    }
                }
                else if (head.second != tail.second)
                {
                    // Move tail to the head on y-axis
                    if (head.second > tail.second)
                    {
                        tail.second++;
                    }
                    else
                    {
                        tail.second--;
                    }
                }
            }

            // Insert new tail position
            visited.insert(tail);
        }
    }
    cout << "Number of visited tiles: " << visited.size() << endl;
    
    inputFile.close();
    return 0;
}
