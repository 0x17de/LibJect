#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H


#include <string>
#include <vector>


enum class SymbolType
{
    Unknown,
    Function,
    File,
    Object,
    Section
};

class ElfSymbolTable;
class ElfSectionStringTable;

struct Symbol
{
    Symbol(const std::string& name, size_t address, size_t size, SymbolType type);
    ~Symbol();

    std::string name;
    size_t address;
    size_t size;
    SymbolType type;
};

class SymbolTable
{
public:
    SymbolTable();
    ~SymbolTable();

    void add(const std::string& name, size_t value, size_t size, SymbolType type);
    void read(const ElfSymbolTable& symbolTable, const ElfSectionStringTable& stringTable);
    Symbol* find(const std::string& name);
    SymbolType getType(unsigned char symInfo) const;
    char typeToChar(SymbolType symbolType) const;

    std::vector<Symbol> symbols;
};

#endif // SYMBOLTABLE_H
