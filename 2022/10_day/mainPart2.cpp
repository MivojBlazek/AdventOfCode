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

    string operation;
    int registerX = 1; // Starting position
    int cycle = -1;

    cout << "CRT:";
    while (getline(inputFile, operation))
    {
        if (operation.substr(0, 4) == "noop")
        {
            cycle++;
            if (cycle % 40 == 0)
            {
                cout << endl;
            }

            // Print lit or dark point
            if (abs(cycle % 40 - registerX) <= 1)
            {
                cout << "#";
            }
            else
            {
                cout << ".";
            }
        }
        else if (operation.substr(0, 4) == "addx")
        {
            int value = stoi(operation.substr(5));

            for (int i = 0; i < 2; i++)
            {
                cycle++;
                if (cycle % 40 == 0)
                {
                    cout << endl;
                }

                // Print lit or dark point
                if (abs(cycle % 40  - registerX) <= 1)
                {
                    cout << "#";
                }
                else
                {
                    cout << ".";
                }
            }
            registerX += value;
        }
    }
    inputFile.close();
    cout << endl;
    
    return 0;
}
