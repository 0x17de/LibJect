#include <iostream>
#include <stdexcept>
#include <string>

#include "LdResolver.h"
#include "ELF/ElfParser.h"
#include "ELF/ElfProgramHeader.h"
#include "SymbolTable.h"
#include "Process.h"
#include "ProcMap.h"

using namespace std;

LdResolver::LdResolver(ElfParser& elfParser, const Process& process)
:
    process(process)
{
    string interpreterPath = elfParser.elfProgramHeader->getInterpreterPath();
    if (interpreterPath.empty())
        throw runtime_error("INTERP empty: no alternatives implemented yet");

    ProcMap procMap(process.pid);
    std::list<ProcEntry*> entryLdList = procMap.findLibrary("libdl");
    cout << entryLdList.size() << endl;
    if (entryLdList.size() > 0)
    {
        string libPath = entryLdList.front()->path;
        ElfParser elfParser(libPath);
    }
    else
    {
        throw runtime_error("libdl was not linked!");
    }

    // find interp in procmap
    // find ld
    // find libc
    // find libdl

    // find malloc in libc
    // find dlopen in dl
}

LdResolver::~LdResolver()
{
}

void LdResolver::resolve(Symbol* symbol)
{
    // symbol->address = 1;
}
