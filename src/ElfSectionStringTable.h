#ifndef ELFSECTIONSTRINGTABLEHEADER_H
#define ELFSECTIONSTRINGTABLEHEADER_H

#include <elf.h>
#include <vector>
#include <string>

class ElfSectionStringTable
{
public:
    ElfSectionStringTable(std::ifstream& elfIn, const Elf64_Shdr* header);
    std::string getName(const Elf64_Shdr* header) const;
    std::string getName(size_t position) const;

    const Elf64_Shdr* header;

private:
    std::vector<char> strings;
};

#endif // ELFSECTIONSTRINGTABLEHEADER_H
