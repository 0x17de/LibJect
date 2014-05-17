#include <stdexcept>
#include <iostream>
#include <string>

#include <cstdlib>
#include <cstring>

#include "ELF/ElfParser.h"
#include "ELF/ElfHeader.h"
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

    if (!elfParser.elfHeader->isArch_x86_64())
        throw runtime_error("Architecture not yet implemented");

    SymbolTable& symbolTable = *elfParser.symbolTable.get();
    const Symbol* sMalloc = symbolTable.find("malloc");
    if (!sMalloc)
    {
        cout << "'malloc' was not dynamically linked" << endl;
        exit(1);
    }
    else
    {
        cout << "'malloc' found at 0x" << hex << sMalloc->address << endl;
    }

    string libraryToInject{"./libtest.so"};

    vector<char> injectData;
    injectData.resize(libraryToInject.size() + 1);
    memcpy(injectData.data(), libraryToInject.c_str(), libraryToInject.length() + 1);

    // spawn and wait when starting child
    // http://www.linuxjournal.com/article/6100

    Process p("./printloop", "printloop", {});

    p.saveRegs();

    // modify registers
    auto regs = p.getRegs();
    regs.rsp -= 128; // http://en.wikipedia.org/wiki/Red_zone_(computing)
    p.setRegs(regs);


    p.backupStack(4);
    // @TODO: inject here
    p.restoreStack();

    p.restoreRegs();

    p.cont();
    p.wait();

    return 0;
}
