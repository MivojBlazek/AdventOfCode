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
#include <vector>
#include <sstream>
#include <any>

using namespace std;

vector<any> parseList(const string &str, size_t &pos)
{
    vector<any> result;
    while (pos < str.size())
    {
        if (str[pos] == '[')
        {
            ++pos; // skip '['
            result.push_back(parseList(str, pos));
        }
        else if (isdigit(str[pos]))
        {
            int num = 0;
            while (pos < str.size() && isdigit(str[pos]))
            {
                num = num * 10 + (str[pos] - '0');
                ++pos;
            }
            result.push_back(num);
        }
        else if (str[pos] == ']')
        {
            ++pos; // skip ']'
            return result;
        }
        else
        {
            ++pos; // skip any other characters like ','
        }
    }
    return result;
}

int compareLists(const vector<any> &list1, const vector<any> &list2)
{
    for (size_t i = 0; i < min(list1.size(), list2.size()); ++i)
    {
        if (list1[i].type() == typeid(int) && list2[i].type() == typeid(int))
        {
            int num1 = any_cast<int>(list1[i]);
            int num2 = any_cast<int>(list2[i]);
            if (num1 < num2) return 1;
            if (num1 > num2) return -1;
        }
        else if (list1[i].type() == typeid(vector<any>) && list2[i].type() == typeid(vector<any>))
        {
            int cmp = compareLists(any_cast<vector<any>>(list1[i]), any_cast<vector<any>>(list2[i]));
            if (cmp != 0) return cmp;
        }
        else if (list1[i].type() == typeid(vector<any>))
        {
            vector<any> list2Wrapper{list2[i]};
            int cmp = compareLists(any_cast<vector<any>>(list1[i]), list2Wrapper);
            if (cmp != 0) return cmp;
        }
        else
        {
            vector<any> list1Wrapper{list1[i]};
            int cmp = compareLists(list1Wrapper, any_cast<vector<any>>(list2[i]));
            if (cmp != 0) return cmp;
        }
    }
    if (list1.size() < list2.size()) return 1;
    if (list1.size() > list2.size()) return -1;
    return 0;
}

int main()
{
    ifstream inputFile("input.in");
    if (!inputFile.is_open())
    {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    string line1;
    string line2;
    int pair = 1;
    int rightOrder = 0;
    while (!inputFile.eof())
    {
        // Loading pairs of lists
        getline(inputFile, line1);
        if (line1.empty())
        {
            getline(inputFile, line1);
        }
        getline(inputFile, line2);

        size_t pos1 = 0, pos2 = 0;
        vector<any> parsedLine1 = parseList(line1, pos1);
        vector<any> parsedLine2 = parseList(line2, pos2);

        if (compareLists(parsedLine1, parsedLine2) == 1)
        {
            rightOrder += pair;
        }
        pair++;
    }

    inputFile.close();
    cout << "Sum of right ordered lists: " << rightOrder << endl;

    return 0;
}
