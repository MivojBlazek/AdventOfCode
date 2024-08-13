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

using namespace std;

int main()
{
    ifstream inputFile("input.in");
    if (!inputFile.is_open())
    {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    string firstLine;
    string secondLine;
    string thirdLine;
    int priority = 0;
    while (getline(inputFile, firstLine))
    {
        getline(inputFile, secondLine);
        getline(inputFile, thirdLine);
        for (char &character : firstLine)
        {
            if (secondLine.find(character) != string::npos && thirdLine.find(character) != string::npos)
            {
                if (character >= 'a' && character <= 'z')
                {
                    priority += static_cast<int>(character - 'a' + 1);
                }
                else
                {
                    priority += static_cast<int>(character - 'A' + 27);
                }
                break;
            }
        }
    }

    cout << "Sum of all priorities: " << priority << endl;

    inputFile.close();
    return 0;
}
