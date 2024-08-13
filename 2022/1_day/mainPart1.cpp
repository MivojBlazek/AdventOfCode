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
    int sum = 0;
    int max = 0;
    while (getline(inputFile, line))
    {
        if (line.empty())
        {
            if (sum > max)
            {
                max = sum;
            }
            sum = 0;
        }
        else
        {
            sum += stoi(line);
        }
    }
    if (sum > max)
    {
        max = sum;
    }

    cout << "Maximal number of calories that any elf has: " << max << endl;

    inputFile.close();
    return 0;
}