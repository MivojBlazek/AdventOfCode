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
    int sum = 0;
    int max[]{0, 0, 0};
    while (getline(inputFile, line))
    {
        if (line.empty())
        {
            // Always switch higher with first item in array (smallest after sorting)
            if (sum > max[0])
            {
                max[0] = sum;
                sort(max, max + 3);
            }
            sum = 0;
        }
        else
        {
            sum += stoi(line);
        }
    }
    if (sum > max[0])
    {
        max[0] = sum;
    }

    // Make a sum of all maximums
    sum = 0;
    for (int maximum : max)
    {
        sum += maximum;
    }

    cout << "The highest sum of calories that carry 3 elves: " << sum << endl;

    inputFile.close();
    return 0;
}