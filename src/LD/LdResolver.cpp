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

    procMap.reset(new ProcMap(process.pid));

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

bool LdResolver::resolve(const std::string& libname, Symbol* symbol)
{
    std::list<ProcEntry*> entryLdList = procMap->findLibrary("libdl");
    cout << entryLdList.size() << endl;
    if (entryLdList.size() > 0)
    {
        ProcEntry* libEntry = entryLdList.front();
        string libPath = libEntry->path;
        ElfParser elfParser(libPath);
        Symbol* symDlopen = elfParser.symbolTable->find(symbol->name);

        if (symDlopen == 0)
            return false;

        cout << "dlopen found at 0x" << hex << symDlopen->address << " starts at 0x" << libEntry->addressBegin << endl;
        symbol->address = symDlopen->address + libEntry->addressBegin;

        return true;
    }
    return false;
}
