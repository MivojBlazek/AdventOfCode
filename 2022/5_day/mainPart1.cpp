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
#include <vector>
#include <stack>

using namespace std;

int main()
{
    ifstream inputFile("input.in");
    if (!inputFile.is_open())
    {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    // Filling vector with current position of towers
    vector<string> lines;
    string line;
    do
    {
        getline(inputFile, line);
        lines.push_back(line);
    } while (!line.empty());

    // Separating to each columns
    vector<stack<char>> columns(9);
    for (auto iterator = lines.rbegin() + 2; iterator != lines.rend(); iterator++)
    {
        line = *iterator;

        for (int i = 0; i < 9; i++)
        {
            char crate = line[1 + i * 4];
            if (crate != ' ')
            {
                columns[i].push(crate);
            }
        }
    }

    while (getline(inputFile, line))
    {
        // Moves
        string withoutMove = line.substr(line.find(" ") + 1);
        int count = stoi(withoutMove.substr(0, withoutMove.find(" ")));
        string withoutFrom = withoutMove.substr(withoutMove.find(" from ") + sizeof(" from ") - 1);
        int from = stoi(withoutFrom.substr(0, withoutFrom.find(" "))) - 1;
        int to = stoi(line.substr(line.find_last_of(" ") + 1)) - 1;

        for (int i = 0; i < count; i++)
        {
            if (columns[from].empty())
            {
                return 1;
            }
            char movingCharacter = columns[from].top();
            columns[from].pop();
            columns[to].push(movingCharacter);
        }
    }

    // Read on tops
    string topChars;
    for (int i = 0; i < 9; i++)
    {
        topChars.push_back(columns[i].top());
    }

    cout << "Characters on top of each column: " << topChars << endl;

    inputFile.close();
    return 0;
}
