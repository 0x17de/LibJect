#include <iostream>
#include "SymbolTable.h"
#include "ElfSymbolTable.h"
#include "ElfSectionStringTable.h"

using namespace std;

enum class SymbolType
{
    Unknown,
    Function,
    File,
    Object,
    Section
};

Symbol::Symbol(const std::string& name, size_t address, size_t size, SymbolType type)
:
    name(name),
    address(address),
    size(size),
    type(type)
{
}

Symbol::~Symbol()
{
}

SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
}

void SymbolTable::add(const std::string& name, size_t value, size_t size, SymbolType type)
{
    symbols.push_back({name, value, size, type});
}

void SymbolTable::read(const ElfSymbolTable& symbolTable, const ElfSectionStringTable& stringTable)
{
    int symbolCount = symbolTable.getSymbolCount();
    cout << "Reading " << symbolCount << " symbols into symbol table" << endl;

    for(int i = 0; i < symbolCount; ++i)
    {
        const Elf64_Sym* sym = symbolTable.getSymbol(i);
        string name = stringTable.getName(sym->st_name);
        SymbolType symbolType = getType(sym->st_info);
        cout << " [" << typeToChar(symbolType) << "]" << name;
        add(name, sym->st_value, sym->st_size, symbolType);
    }
    cout << endl;

    cout << endl;
}

char SymbolTable::typeToChar(SymbolType symbolType) const
{
    switch(symbolType)
    {
    case SymbolType::Function:
        return 'F';
    case SymbolType::File:
        return 'D';
    case SymbolType::Object:
        return 'O';
    case SymbolType::Section:
        return 'S';
    case SymbolType::Unknown:
        return '?';
    }
    return '!';
}

SymbolType SymbolTable::getType(unsigned char symInfo) const
{
    int val = ELF64_ST_TYPE(symInfo);
    switch(val)
    {
    case STT_FUNC:
        return SymbolType::Function;
    case STT_FILE:
        return SymbolType::File;
    case STT_OBJECT:
        return SymbolType::Object;
    case STT_SECTION:
        return SymbolType::Section;
    }
    return SymbolType::Unknown;
}
