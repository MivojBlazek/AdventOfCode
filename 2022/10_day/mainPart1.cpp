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

    string operation;
    int registerX = 1; // Starting position
    int cycle = 0;
    int sum = 0;

    while (getline(inputFile, operation))
    {
        if (operation.substr(0, 4) == "noop")
        {
            cycle++;
            // 20. cycle and every 40. after that
            if (cycle % 40 == 20)
            {
                sum += (cycle * registerX);
                cout << "Cycle: " << cycle << endl;
                cout << "Value in register: " << registerX << endl << endl;
            }
        }
        else if (operation.substr(0, 4) == "addx")
        {
            int value = stoi(operation.substr(5));

            for (int i = 0; i < 2; i++)
            {
                cycle++;
                // 20. cycle and every 40. after that
                if (cycle % 40 == 20)
                {
                    sum += (cycle * registerX);
                    cout << "Cycle: " << cycle << endl;
                    cout << "Value in register: " << registerX << endl << endl;
                }
            }
            registerX += value;
        }
    }
    inputFile.close();

    cout << "Sum of signal strengths: " << sum << endl;
    
    return 0;
}
