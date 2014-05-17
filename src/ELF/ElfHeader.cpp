#include "ElfHeader.h"

using namespace std;

ElfHeader::ElfHeader(std::ifstream& file)
{
    file.seekg(0);
    file.read((char*)&header, sizeof(header));
}

ElfHeader::~ElfHeader()
{
}

bool ElfHeader::isArch_x86_32() const
{
    return header.e_machine == EM_386;
}

bool ElfHeader::isArch_x86_64() const
{
    return header.e_machine == EM_X86_64;
}

size_t ElfHeader::getSectionHeaderOffset() const
{
    return header.e_shoff;
}

size_t ElfHeader::getSectionHeaderEntryCount() const
{
    return header.e_shnum;
}

size_t ElfHeader::getSectionHeaderNumber() const
{
    return header.e_shnum;
}

size_t ElfHeader::getSectionHeaderSize() const
{
    return header.e_shnum * header.e_shentsize;
}

size_t ElfHeader::getSectionStringTableIndex() const
{
    return header.e_shstrndx;
}

size_t ElfHeader::getProgramHeaderOffset() const
{
    return header.e_phoff;
}

size_t ElfHeader::getProgramHeaderEntryCount() const
{
    return header.e_phnum;
}

size_t ElfHeader::getProgramHeaderNumber() const
{
    return header.e_phnum;
}

size_t ElfHeader::getProgramHeaderSize() const
{
    return header.e_phnum * header.e_phentsize;
}

