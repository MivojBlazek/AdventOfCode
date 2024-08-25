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
#include <vector>
#include <sstream>
#include <any>

using namespace std;


void printList(const vector<any>& list);

void printAny(const any& a)
{
    if (a.type() == typeid(int))
    {
        cout << any_cast<int>(a);
    }
    else if (a.type() == typeid(vector<any>))
    {
        printList(any_cast<const vector<any>&>(a));
    }
}

void printList(const vector<any>& list)
{
    cout << "[";
    for (size_t i = 0; i < list.size(); i++)
    {
        printAny(list[i]);
        if (i < list.size() - 1)
        {
            cout << ",";
        }
    }
    cout << "]";
}

vector<any> parseList(const string &str, size_t &pos)
{
    vector<any> result;
    while (pos < str.size())
    {
        if (str[pos] == '[')
        {
            pos++;
            result.push_back(parseList(str, pos));
        }
        else if (isdigit(str[pos]))
        {
            int num = 0;
            while (pos < str.size() && isdigit(str[pos]))
            {
                num = num * 10 + (str[pos] - '0');
                pos++;
            }
            result.push_back(num);
        }
        else if (str[pos] == ']')
        {
            pos++;
            return result;
        }
        else
        {
            pos++;
        }
    }
    return result;
}

int compareLists(const vector<any> &list1, const vector<any> &list2)
{
    for (size_t i = 0; i < min(list1.size(), list2.size()); i++)
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

    string line;
    vector<vector<any>> packets;

    // Read packets
    while (getline(inputFile, line))
    {
        if (!line.empty())
        {
            size_t pos = 0;
            packets.push_back(parseList(line, pos));
        }
    }
    inputFile.close();

    // Add new packets
    size_t pos = 0;
    packets.push_back(parseList("[[2]]", pos));
    pos = 0;
    packets.push_back(parseList("[[6]]", pos));

    // Sort packets according to comparing
    sort(packets.begin(), packets.end(), [](const vector<any>& a, const vector<any>& b)
    {
        return compareLists(a, b) == 1;
    });

    // Print packets
    for (size_t i = 0; i < packets.size(); i++)
    {
        cout << "Packet " << i + 1 << ": ";
        printList(packets[i]);
        cout << endl;
    }

    return 0;
}
