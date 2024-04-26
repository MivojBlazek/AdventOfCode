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
#include <unordered_map>

using namespace std;

int main()
{
    ifstream inputFile("input.in");
    if (!inputFile.is_open())
    {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    unordered_map<string, char> numbers{
        {"one",   '1'},
        {"two",   '2'},
        {"three", '3'},
        {"four",  '4'},
        {"five",  '5'},
        {"six",   '6'},
        {"seven", '7'},
        {"eight", '8'},
        {"nine",  '9'}
    };

    string line;
    int sum = 0;
    while (getline(inputFile, line))
    {
        // make numbers from their text representation in every line
        bool isFirstInLine = true;
        for (size_t i = 0; i < line.length(); i++)
        {
            if (isdigit(line[i]))
            {
                isFirstInLine = false;
            }

            for (auto pair : numbers)
            {
                string textNumber = pair.first;
                char charNumber = pair.second;

                if (line.substr(i, textNumber.length()) == textNumber)
                {
                    if (isFirstInLine)
                    {
                        line.replace(i, textNumber.length(), 1, charNumber);
                        isFirstInLine = false;
                    }
                    else
                    {
                        line.replace(i, 1, 1, charNumber);
                    }
                }
            }
        }

        // find first and last number
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

        // should have both digits -> concat to int
        int numberInLine = (first - '0') * 10 + (last - '0');
        sum += numberInLine;
    }

    cout << "Sum of all numbers (text too) is: " << sum << endl;

    inputFile.close();
    return 0;
}