#include "directory.h"
#include <iostream>

Directory::Directory(Directory *_parent, string _name)
    : fileSizeAdded{false}
{
    size = 0;
    parent = _parent;
    name = _name;
}

Directory::~Directory()
{
    for (Directory *subDir : subDirectories)
    {
        delete subDir;
    }
    delete this;
}

int Directory::getSize()
{
    return size;
}

void Directory::addSize(int _size)
{
    if (!fileSizeAdded)
    {
        size += _size;
        fileSizeAdded = true;
    }
}

void Directory::addSizeFromSubDirectories()
{
    for (Directory *subDir : subDirectories)
    {
        if (!subDir->isLastDirectory())
        {
            subDir->addSizeFromSubDirectories();
        }
        size += subDir->getSize();
    }
}

void Directory::addSubDir(string _name)
{
    for (Directory *subDir : subDirectories)
    {
        if (subDir->getName() == _name)
        {
            return;
        }
    }
    Directory *newDir = new Directory(this, _name);
    subDirectories.push_back(newDir);
}

string Directory::getName()
{
    return name;
}

Directory *Directory::goToDir(string _name)
{
    for (Directory *subDir : subDirectories)
    {
        if (subDir->getName() == _name)
        {
            return subDir;
        }
    }
    return nullptr;
}

Directory *Directory::getParent()
{
    return parent;
}

bool Directory::isLastDirectory()
{
    if (subDirectories.empty())
    {
        return true;
    }
    return false;
}

void Directory::printTree(int indentLevel)
{
    for (int i = 0; i < indentLevel; i++)
    {
        std::cout << "    ";
    }
    std::cout << name << " (Size: " << size << ")" << std::endl;

    // Recursively print all directories
    for (Directory *subDir : subDirectories)
    {
        subDir->printTree(indentLevel + 1);
    }
}

int Directory::sumOfSmallDirectories(int maxSize)
{
    int sum = 0;
    if (size <= maxSize)
    {
        sum += size;
    }

    for (Directory *subDir : subDirectories)
    {
        sum += subDir->sumOfSmallDirectories(maxSize);
    }
    return sum;
}

void Directory::printOnlyAbove(int minSize)
{
    if (size >= minSize)
    {
        std::cout << name << " (Size: " << size << ")" << std::endl;
    }

    for (Directory *subDir : subDirectories)
    {
        subDir->printOnlyAbove(minSize);
    }
}
