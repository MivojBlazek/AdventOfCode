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
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

struct Item
{
    char height;
    int x;
    int y;
};

vector<pair<int, int>> getNeighbors(Item *currentItem, const vector<vector<Item>> &field)
{
    vector<pair<int, int>> neighbors;
    int rows = field.size();
    int cols = field[0].size();

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int dir = 0; dir < 4; dir++)
    {
        int newX = currentItem->x + dx[dir];
        int newY = currentItem->y + dy[dir];

        if (newX >= 0 && newX < cols && newY >= 0 && newY < rows)
        {
            if ((currentItem->height - field[newY][newX].height) >= -1 )
            {
                neighbors.push_back({newX, newY});
            }
        }
    }
    return neighbors;
}

int bfsShortestPath(vector<vector<Item>> &field, int startX, int startY, int endX, int endY)
{
    int rows = field.size();
    int cols = field[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    queue<tuple<int, int, int>> q;
    q.push({startX, startY, 0});
    visited[startY][startX] = true;

    while (!q.empty())
    {
        auto [x, y, steps] = q.front();
        q.pop();

        if (x == endX && y == endY)
        {
            return steps;
        }

        for (auto [newX, newY] : getNeighbors(&field[y][x], field))
        {
            if (!visited[newY][newX])
            {
                visited[newY][newX] = true;
                q.push({newX, newY, steps + 1});
            }
        }
    }
    return -1;
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
    vector<vector<Item>> field;

    vector<Item> startingPositions;
    int endingPositionX = -1;
    int endingPositionY = -1;

    int i = 0;
    while (getline(inputFile, line))
    {
        int j = 0;
        vector<Item> lineVec;
        for (char character : line)
        {
            Item item;
            item.height = character;
            item.x = j;
            item.y = i;
            if (character == 'S' || character == 'a')
            {
                item.height = 'a';
                startingPositions.push_back(item);
            }
            else if (character == 'E')
            {
                endingPositionX = j;
                endingPositionY = i;
                item.height = 'z';
            }
            lineVec.push_back(item);
            j++;
        }
        field.push_back(lineVec);
        i++;
    }
    inputFile.close();

    int minPath = 99999;
    for (Item &item : startingPositions)
    {
        int pathLength = bfsShortestPath(field, item.x, item.y, endingPositionX, endingPositionY);
        if (pathLength < minPath && pathLength != -1)
        {
            minPath = pathLength;
        }
    }

    cout << "Length of shortest path: " << minPath << endl;

    return 0;
}
