/**
 * @file mainPart2.cpp
 * 
 * AdventOfCode
 * 
 * @author MivojBlazek
*/

#include "directory.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream inputFile("input.in");
    if (!inputFile.is_open())
    {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    Directory *rootDirectory = new Directory(nullptr, "/");
    Directory *currentDir = rootDirectory;
    string line;
    while (getline(inputFile, line))
    {
        if (line.front() == '$')
        {
            // Command
            if (line.substr(2, 2) == "cd")
            {
                string whereToGo = line.substr(5);
                if (whereToGo == "..")
                {
                    currentDir = currentDir->getParent();
                }
                else if (whereToGo == "/")
                {
                    currentDir = rootDirectory;
                }
                else
                {
                    currentDir = currentDir->goToDir(whereToGo);
                }
            }
            else if (line.substr(2, 2) == "ls")
            {
                // Only list of current directory supported so nothing to do
                continue;
            }
        }
        else
        {
            // Statements after ls
            int fileSize = 0;
            do
            {
                if (line.substr(0, 3) == "dir")
                {
                    // Subdirectory
                    currentDir->addSubDir(line.substr(4));
                }
                else
                {
                    // File
                    fileSize += stoi(line.substr(0, line.find(" ")));
                }
                getline(inputFile, line);
                if (inputFile.eof())
                {
                    break;
                }
            } while (line.front() != '$');

            // Add size of files to directory data
            currentDir->addSize(fileSize);

            if (line.substr(2, 2) == "cd")
            {
                string whereToGo = line.substr(5);
                if (whereToGo == "..")
                {
                    currentDir = currentDir->getParent();
                }
                else if (whereToGo == "/")
                {
                    currentDir = rootDirectory;
                }
                else
                {
                    currentDir = currentDir->goToDir(whereToGo);
                }
            }
        }
    }
    rootDirectory->addSizeFromSubDirectories();
    
    int sizeOfRoot = rootDirectory->getSize() - 70000000 + 30000000;
    if (sizeOfRoot > 0)
    {
        // Not enough space for update
        rootDirectory->printOnlyAbove(sizeOfRoot);
    }

    inputFile.close();
    return 0;
}
