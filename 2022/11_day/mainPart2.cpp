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
#include <functional>
#include <map>

using namespace std;

struct Monkey
{
    vector<unsigned long long> startingItems;
    function<unsigned long long(unsigned long long)> operation;
    function<bool(unsigned long long)> test;
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

    vector<unsigned long long> divisors;

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
            unsigned long long item;
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
                unsigned long long value;
                if (operation.substr(2) != "old")
                {
                    value = stoi(operation.substr(2));
                    monkeys[monkeyIndex].operation = [value](unsigned long long old)
                    {
                        return old * value;
                    };
                }
                else
                {
                    monkeys[monkeyIndex].operation = [](unsigned long long old)
                    {
                        return old * old;
                    };
                }
            }
            else if (operation.front() == '+')
            {
                unsigned long long value = stoi(operation.substr(2));
                monkeys[monkeyIndex].operation = [value](unsigned long long old)
                {
                    return old + value;
                };
            }
        }
        else if (line.find("Test: divisible by") != string::npos)
        {
            unsigned long long divisor = stoi(line.substr(line.find("by") + 3));
            divisors.push_back(divisor);
            monkeys[monkeyIndex].test = [divisor](unsigned long long value)
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

    unsigned long long worryLevelDivisor = 1;
    for (auto divisor : divisors)
    {
        worryLevelDivisor *= divisor;
    }
    while (true)
    {
        // Monkey inspects item
        for (unsigned long long item : monkeys[monkeyIndex].startingItems)
        {
            monkeys[monkeyIndex].inspecting++;
            unsigned long long worryLevel = monkeys[monkeyIndex].operation(item);
            if (worryLevel > worryLevelDivisor)
            {
                worryLevel %= worryLevelDivisor;
            }

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
        if (round == static_cast<int>(10000 * monkeys.size()))
        {
            break;
        }
        round++;
        monkeyIndex = ((round - 1) % monkeys.size());
    }

    cout << "After 10000 rounds:" << endl;

    vector<int> inspectingNumbers;

    for (auto monkey : monkeys)
    {
        inspectingNumbers.push_back(monkey.second.inspecting);
        cout << "Monkey " << monkey.first << ": " << monkey.second.inspecting << " inspected items" << endl;
    }

    sort(inspectingNumbers.begin(), inspectingNumbers.end());
    unsigned long long firstNum = static_cast<unsigned long long>(inspectingNumbers[inspectingNumbers.size() - 1]);
    unsigned long long secondNum = static_cast<unsigned long long>(inspectingNumbers[inspectingNumbers.size() - 2]);
    cout << "Monkey business: " << firstNum * secondNum << endl;

    return 0;
}
