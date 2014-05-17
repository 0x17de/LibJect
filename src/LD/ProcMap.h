#ifndef PROCMAP_H
#define PROCMAP_H

#include <string>
#include <list>
#include <unistd.h>

struct ProcEntry
{
    ProcEntry(std::string addressRange,
              std::string permissions,
              std::string offset,
              std::string device,
              std::string inode,
              std::string path);
    size_t addressBegin;
    size_t addressEnd;
    std::string permissions;
    std::string offset;
    std::string device;
    std::string inode;
    std::string path;
};

class ProcMap
{
public:
    ProcMap(pid_t pid);
    ~ProcMap();

    std::list<ProcEntry*> findLibrary(const std::string& libraryName);

    std::list<ProcEntry> procList;
};

#endif // PROCMAP_H
