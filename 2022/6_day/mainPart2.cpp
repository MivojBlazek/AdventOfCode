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
#include <unordered_set>

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
    getline(inputFile, line);
    inputFile.close();

    for (long unsigned int i = 0; i <= line.length() - 14; i++)
    {
        string subString = line.substr(i, 14);
        unordered_set<char> uniqueChars(subString.begin(), subString.end());

        if (uniqueChars.size() == 14)
        {
            cout << "First position without same characters: " << i + 14 << endl;
            return 0;
        }
    }
    return 0;
}
