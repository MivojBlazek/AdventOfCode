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

    string line;
    int score = 0;
    while (getline(inputFile, line))
    {
        char opponent = line[0];
        char need = line.back();
        char me = 'X';
        switch (opponent)
        {
            case 'A':
                if (need == 'X')
                {
                    me = 'Z';
                    score += 0;
                }
                else if (need == 'Y')
                {
                    score += 3;
                }
                else // (need == 'Z')
                {
                    me = 'Y';
                    score += 6;
                }
                break;
            case 'B':
                if (need == 'X')
                {
                    score += 0;
                }
                else if (need == 'Y')
                {
                    me = 'Y';
                    score += 3;
                }
                else // (need == 'Z')
                {
                    me = 'Z';
                    score += 6;
                }
                break;
            case 'C':
                if (need == 'X')
                {
                    me = 'Y';
                    score += 0;
                }
                else if (need == 'Y')
                {
                    me = 'Z';
                    score += 3;
                }
                else // (need == 'Z')
                {
                    score += 6;
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