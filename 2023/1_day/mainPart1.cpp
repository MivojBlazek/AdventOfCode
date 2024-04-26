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
    while (getline(inputFile, line))
    {
        char first, last;
        bool isFirst = true;
        for (char character : line)
        {
            if (isdigit(character))
            {
                if (isFirst)
                {
                    first = character;
                    isFirst = false;
                }
                last = character;
            }
        }

        // should have both digits
        int numberInLine = (first - '0') * 10 + (last - '0');
        sum += numberInLine;
    }

    cout << "Sum of all numbers is: " << sum << endl;

    inputFile.close();
    return 0;
}