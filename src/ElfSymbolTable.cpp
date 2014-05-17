#include <iostream>
#include <fstream>
#include "ElfSymbolTable.h"

using namespace std;

ElfSymbolTable::ElfSymbolTable(std::ifstream& elfIn, Elf64_Shdr* header)
:
    header(header)
{
    symbolCount = header->sh_size / header->sh_entsize;
    cout << "Symboltable Offset: 0x" << hex << header->sh_offset << dec << ", Size: " << header->sh_size << ", SymCount: " << symbolCount << endl;
    cout.flush();
    symbols.resize(symbolCount);
    elfIn.seekg(header->sh_offset);
    elfIn.read((char*)symbols.data(), header->sh_size);
}

ElfSymbolTable::~ElfSymbolTable()
{
}

int ElfSymbolTable::getSymbolCount() const
{
    return symbolCount;
}

const Elf64_Sym* ElfSymbolTable::getSymbol(size_t index) const
{
    return &symbols.at(index);
}
