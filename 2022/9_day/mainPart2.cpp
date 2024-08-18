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
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main()
{
    ifstream inputFile("input.in");
    if (!inputFile.is_open())
    {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    vector<pair<int, int>> snake(10, {0, 0});
    set<pair<int, int>> visited;
    visited.insert(snake.back());

    string direction;
    int steps;
    while (inputFile >> direction >> steps)
    {
        for (int i = 0; i < steps; i++)
        {
            // Move head
            if (direction == "R")
            {
                snake[0].first += 1;
            }
            else if (direction == "L")
            {
                snake[0].first -= 1;
            }
            else if (direction == "U")
            {
                snake[0].second += 1;
            }
            else if (direction == "D")
            {
                snake[0].second -= 1;
            }


            for (int j = 1; j < 10; j++)
            {
                int dx = snake[j - 1].first - snake[j].first;
                int dy = snake[j - 1].second - snake[j].second;

                // Move other parts of tail
                if (abs(dx) > 1 || abs(dy) > 1)
                {
                    if (dx != 0 && dy != 0)
                    {
                        // Move other parts diagonally
                        snake[j].first += (dx > 0) ? 1 : -1;
                        snake[j].second += (dy > 0) ? 1 : -1;
                    }
                    else if (dx != 0)
                    {
                        // Move other parts in x-axis
                        snake[j].first += dx / 2;
                    }
                    else if (dy != 0)
                    {
                        // Move other parts in y-axis
                        snake[j].second += dy / 2;
                    }
                }

                // Insert new tail position
                visited.insert(snake.back());
            }
        }
    }
    cout << "Number of visited tiles: " << visited.size() << endl;
    
    inputFile.close();
    return 0;
}
