#include <stdexcept>
#include <iostream>
#include <string>

#include <cstdlib>
#include <cstring>

#include <thread>
#include <chrono>

#include <sys/wait.h>

#include "ELF/ElfParser.h"
#include "ELF/ElfHeader.h"
#include "LD/LdResolver.h"
#include "SymbolTable.h"
#include "Process.h"

using namespace std;

int main()
{
    string fileName = "./crackme";
    cout << "Parsing ELF: " << fileName << endl;

    ElfParser elfParser(fileName);

    cout << "Is 32 bits: " << boolalpha << elfParser.elfHeader->isArch_x86_32() << endl;
    cout << "Is 64 bits: " << boolalpha << elfParser.elfHeader->isArch_x86_64() << endl;
    cout << endl;

    if (!elfParser.elfHeader->isArch_x86_64())
        throw runtime_error("Architecture not yet implemented");


    SymbolTable& symbolTable = *elfParser.symbolTable.get();
    Symbol* sMalloc = symbolTable.find("malloc");
    if (!sMalloc)
        throw runtime_error("'malloc' was not dynamically linked");

    Symbol* sStart = symbolTable.find("main");
    if (!sStart)
    {
        throw runtime_error("Start method not found");
    }
    cout << "Start functon: 0x" << hex << sStart->address << endl;


    string libraryToInject{"./libtest.so"};

    vector<char> injectData;
    injectData.resize(libraryToInject.size() + 1);
    memcpy(injectData.data(), libraryToInject.c_str(), libraryToInject.length() + 1);

    // spawn and wait when starting child
    // http://www.linuxjournal.com/article/6100

    // redirect pipes of child process
    // http://stackoverflow.com/questions/9405985/linux-3-0-executing-child-process-with-piped-stdin-stdout

    Process p(fileName, fileName.substr(fileName.find_last_of('/') + 1), {}, {"LD_PRELOAD=libdl.so"});

    // break at _start function
    {
        Breakpoint breakpoint = p.breakAt(sStart->address);
        p.cont();
        ::wait(0);
        p.removeBreakpoint(breakpoint);

        auto regs = p.getRegs();
        regs.rip -= 1;
        p.setRegs(regs);
    }

    LdResolver ldResolver(elfParser, p);
    ldResolver.resolve(sMalloc);
    cout << "'malloc' found at 0x" << hex << sMalloc->address << endl;

    p.saveRegs();

    // modify registers
    auto regs = p.getRegs();
    regs.rsp -= 128; // http://en.wikipedia.org/wiki/Red_zone_(computing)
    p.setRegs(regs);
    // nullify stack?


    p.backupStack(4);
    // @TODO: inject here
    p.restoreStack();


    p.restoreRegs();

    // this_thread::sleep_for(chrono::seconds(10));

    p.cont();
    p.wait();

    return 0;
}
