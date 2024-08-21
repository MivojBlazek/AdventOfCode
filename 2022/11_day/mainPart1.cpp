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
#include <functional>
#include <map>

using namespace std;

struct Monkey
{
    vector<int> startingItems;
    function<int(int)> operation;
    function<bool(int)> test;
    int trueTarget;
    int falseTarget;
    int inspecting;
};

int main()
{
    ifstream inputFile("input.in");
    if (!inputFile.is_open())
    {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    map<int, Monkey> monkeys;
    string line;
    int monkeyIndex = -1;

    // Filling monkeys structures with data from file
    while (getline(inputFile, line))
    {
        if (line.find("Monkey") != string::npos)
        {
            monkeyIndex = stoi(line.substr(7, line.find(':') - 7));
            monkeys[monkeyIndex] = Monkey();
            monkeys[monkeyIndex].inspecting = 0;
        }
        else if (line.find("Starting items:") != string::npos)
        {
            string items = line.substr(line.find(":") + 2);
            stringstream ss(items);
            int item;
            while (ss >> item)
            {
                monkeys[monkeyIndex].startingItems.push_back(item);
                if (ss.peek() == ',')
                {
                    ss.ignore();
                }
            }
        }
        else if (line.find("Operation: new = old") != string::npos)
        {
            string operation = line.substr(line.find("= old") + 6);
            if (operation.front() == '*')
            {
                int value;
                if (operation.substr(2) != "old")
                {
                    value = stoi(operation.substr(2));
                    monkeys[monkeyIndex].operation = [value](int old)
                    {
                        return old * value;
                    };
                }
                else
                {
                    monkeys[monkeyIndex].operation = [](int old)
                    {
                        return old * old;
                    };
                }
            }
            else if (operation.front() == '+')
            {
                int value = stoi(operation.substr(2));
                monkeys[monkeyIndex].operation = [value](int old)
                {
                    return old + value;
                };
            }
        }
        else if (line.find("Test: divisible by") != string::npos)
        {
            int divisor = stoi(line.substr(line.find("by") + 3));
            monkeys[monkeyIndex].test = [divisor](int value)
            {
                return value % divisor == 0;
            };
        }
        else if (line.find("If true: throw to monkey") != string::npos)
        {
            int nextMonkey = stoi(line.substr(line.find("monkey") + 7));
            monkeys[monkeyIndex].trueTarget = nextMonkey;
        }
        else if (line.find("If false: throw to monkey") != string::npos)
        {
            int nextMonkey = stoi(line.substr(line.find("monkey") + 7));
            monkeys[monkeyIndex].falseTarget = nextMonkey;
        }
    }
    inputFile.close();

    // Processing
    monkeyIndex = 0;
    int round = 1;
    while (true)
    {
        // Monkey inspects item
        for (int item : monkeys[monkeyIndex].startingItems)
        {
            monkeys[monkeyIndex].inspecting++;
            int worryLevel = monkeys[monkeyIndex].operation(item);

            // Worry level divided by 3 and rounded down
            worryLevel /= 3;

            int nextMonkey = -1;
            bool testResult = monkeys[monkeyIndex].test(worryLevel);
            if (testResult)
            {
                nextMonkey = monkeys[monkeyIndex].trueTarget;
            }
            else
            {
                nextMonkey = monkeys[monkeyIndex].falseTarget;
            }

            // Push inspected item to another monkey
            monkeys[nextMonkey].startingItems.push_back(worryLevel);
        }
        // Remove all items from current monkey because it throw them away
        monkeys[monkeyIndex].startingItems.clear();

        // Next monkey turn
        if (round == static_cast<int>(20 * monkeys.size()))
        {
            break;
        }
        round++;
        monkeyIndex = ((round - 1) % monkeys.size());
    }

    cout << "After 20 rounds:" << endl;

    vector<int> inspectingNumbers;

    for (auto monkey : monkeys)
    {
        inspectingNumbers.push_back(monkey.second.inspecting);
        cout << "Monkey " << monkey.first << ": " << monkey.second.inspecting << " inspected items" << endl;
    }

    sort(inspectingNumbers.begin(), inspectingNumbers.end());
    cout << "Monkey business: " << inspectingNumbers[inspectingNumbers.size() - 1] * inspectingNumbers[inspectingNumbers.size() - 2] << endl;

    return 0;
}
