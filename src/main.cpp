#include <stdexcept>
#include <iostream>
#include <ElfParser.h>

using namespace std;

int main()
{
    string fileName = "./crackme";
    cout << "Parsing ELF: " << fileName << endl;

    ElfParser elfParser("./crackme");
    cout << endl;
    cout << "Is 32 bits: " << boolalpha << elfParser.elfHeader.isArch_x86_32() << endl;
    cout << "Is 64 bits: " << boolalpha << elfParser.elfHeader.isArch_x86_64() << endl;

    if (!elfParser.elfHeader.isArch_x86_64())
        throw runtime_error("Architecture not yet implemented");



    return 0;
}
