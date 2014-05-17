#include <stdexcept>
#include <iostream>
#include <ElfParser.h>
#include <ElfHeader.h>

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

    // spawn and wait when starting child
    // http://www.linuxjournal.com/article/6100

    return 0;
}
