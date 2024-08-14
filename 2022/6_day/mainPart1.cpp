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

    for (long unsigned int i = 0; i <= line.length() - 4; i++)
    {
        string subString = line.substr(i, 4);
        unordered_set<char> uniqueChars(subString.begin(), subString.end());

        if (uniqueChars.size() == 4)
        {
            cout << "First position without same characters: " << i + 4 << endl;
            return 0;
        }
    }
    return 0;
}
