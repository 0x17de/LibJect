#ifndef ELFHEADER_H
#define ELFHEADER_H


#include <fstream>
#include <elf.h>

class ElfHeader
{
public:
    ElfHeader(std::ifstream& file);
    ~ElfHeader();

    bool isArch_x86_32() const;
    bool isArch_x86_64() const;

    size_t getSectionHeaderOffset() const;
    size_t getSectionHeaderEntryCount() const;
    size_t getSectionHeaderSize() const;
    size_t getSectionHeaderNumber() const;
    size_t getSectionStringTableIndex() const;

private:
    Elf64_Ehdr header;
};

#endif // ELFHEADER_H
