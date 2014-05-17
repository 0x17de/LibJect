#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "ProcMap.h"

using namespace std;

ProcEntry::ProcEntry(std::string addressRange,
                     std::string permissions,
                     std::string offset,
                     std::string device,
                     std::string inode,
                     std::string path)
:
    permissions(permissions),
    offset(offset),
    device(device),
    inode(inode),
    path(path)
{
    istringstream is(addressRange);
    string line;
    getline(is, line, '-');
    addressBegin = strtoul(line.c_str(), 0, 16);
    getline(is, line);
    addressEnd = strtoul(line.c_str(), 0, 16);
}

ProcMap::ProcMap(pid_t pid)
{
    stringstream ss;
    ss << "/proc/" << pid << "/maps";
    string procMap = ss.str();
    ifstream procIn(procMap.c_str());

    cout << "Reading PROC: " << procMap << endl << endl;

    string line;
    while(getline(procIn, line))
    {
        cout << line << endl;
        istringstream is{line};

        string addressRange, permissions, offset, device, inode, path;
        is >> addressRange;
        is >> permissions;
        is >> offset;
        is >> device;
        is >> inode;
        is >> path;
        cout << path << endl;

        procList.push_back({addressRange, permissions, offset, device, inode, path});
    }

    cout << endl;
}

ProcMap::~ProcMap()
{
}

std::list<ProcEntry*> ProcMap::findLibrary(const std::string& libraryName)
{
    std::list<ProcEntry*> resultList;
    for(ProcEntry& entry : procList)
    {
        if (entry.path.empty())
            continue;
        if (entry.path[0] == '[')
            continue;

        size_t startOfLibName = entry.path.find_last_of('/') + 1;
        size_t endOfLibName = entry.path.find_last_of('-');
        string currentLibName = entry.path.substr(startOfLibName, endOfLibName - startOfLibName);
        cout << currentLibName << endl;
        if (libraryName == currentLibName)
            resultList.push_back(&entry);
    }
    return resultList;
}
