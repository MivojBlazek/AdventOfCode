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
    int score = 0;
    while (getline(inputFile, line))
    {
        char opponent = line[0];
        char me = line.back();
        switch (opponent)
        {
            case 'A':
                if (me == 'Y')
                {
                    score += 6;
                }
                else if (me == 'X')
                {
                    score += 3;
                }
                break;
            case 'B':
                if (me == 'Z')
                {
                    score += 6;
                }
                else if (me == 'Y')
                {
                    score += 3;
                }
                break;
            case 'C':
                if (me == 'X')
                {
                    score += 6;
                }
                else if (me == 'Z')
                {
                    score += 3;
                }
                break;
            default:
                break;
        }
        score += static_cast<int>(me - 'X' + 1);
    }

    cout << "Score after strategy: " << score << endl;

    inputFile.close();
    return 0;
}