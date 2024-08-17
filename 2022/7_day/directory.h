#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>

using namespace std;

class Directory
{
private:
    int size;
    Directory *parent;
    string name;
    vector<Directory *> subDirectories;

    bool fileSizeAdded;

public:
    Directory(Directory *_parent, string _name);
    ~Directory();

    int getSize();
    void addSize(int _size);
    void addSizeFromSubDirectories();
    void addSubDir(string name);
    string getName();
    Directory *goToDir(string _name);
    Directory *getParent();
    bool isLastDirectory();

    void printTree(int indentLevel = 0);
    int sumOfSmallDirectories(int maxSize = 100000);
    void printOnlyAbove(int minSize);
};

#endif // DIRECTORY_H