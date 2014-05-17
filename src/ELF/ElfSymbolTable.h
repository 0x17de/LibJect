#ifndef ELFSYMBOLTABLE_H
#define ELFSYMBOLTABLE_H


#include <vector>
#include <elf.h>

class ElfSymbolTable
{
public:
    ElfSymbolTable(std::ifstream& elfIn, Elf64_Shdr* header);
    ~ElfSymbolTable();

    int getSymbolCount() const;
    const Elf64_Sym* getSymbol(size_t index) const;

    const Elf64_Shdr* header;

private:
    int symbolCount;
    std::vector<Elf64_Sym> symbols;
};

#endif // ELFSYMBOLTABLE_H
