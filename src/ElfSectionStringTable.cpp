#include <iostream>
#include "ElfSectionStringTable.h"

using namespace std;

ElfSectionStringTable::ElfSectionStringTable(std::ifstream& elfIn, const Elf64_Shdr* header)
:
    header(header)
{
    cout << "Stringtable Offset: 0x" << hex << header->sh_offset << dec << ", Size: " << header->sh_size << endl;
    cout.flush();
    strings.resize(header->sh_size);
    elfIn.seekg(header->sh_offset);
    elfIn.read(strings.data(), header->sh_size);
}

std::string ElfSectionStringTable::getName(const Elf64_Shdr* header) const
{
    return string(&strings[header->sh_name]);
}
