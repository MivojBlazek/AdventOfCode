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
    int priority = 0;
    while (getline(inputFile, line))
    {
        string firstHalf = line.substr(0, line.length() / 2);
        string secondHalf = line.substr(line.length() / 2);

        for (char &character : firstHalf)
        {
            if (secondHalf.find(character) != string::npos)
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
