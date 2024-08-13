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

using namespace std;

int main()
{
    ifstream inputFile("input.in");
    if (!inputFile.is_open())
    {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    string line;
    int count = 0;
    while (getline(inputFile, line))
    {
        string firstInterval = line.substr(0, line.find(","));
        string secondInterval = line.substr(line.find(",") + 1);

        int leftBorderFirst = stoi(firstInterval.substr(0, firstInterval.find("-")));
        int rightBorderFirst = stoi(firstInterval.substr(firstInterval.find("-") + 1));

        int leftBorderSecond = stoi(secondInterval.substr(0, secondInterval.find("-")));
        int rightBorderSecond = stoi(secondInterval.substr(secondInterval.find("-") + 1));

        if (leftBorderFirst <= leftBorderSecond && rightBorderSecond <= rightBorderFirst)
        {
            count++;
        }
        else if (leftBorderSecond <= leftBorderFirst && rightBorderFirst <= rightBorderSecond)
        {
            count++;
        }
    }

    cout << "Count of all fully contained intervals: " << count << endl;

    inputFile.close();
    return 0;
}
