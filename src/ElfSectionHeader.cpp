#include <iostream>
#include "ElfSectionHeader.h"

using namespace std;

ElfSectionHeader::ElfSectionHeader(std::ifstream& elfIn, ElfHeader& elfHeader)
:
    elfHeader(elfHeader),
    idSymTab(-1),
    idStrTab(-1)
{
    cout << endl;
    cout << "Reading: SymTab at: " << elfHeader.getSectionStringTableIndex() << endl;
    cout << "Section header location: 0x" << hex << elfHeader.getSectionHeaderOffset() << ", Size: " << dec << elfHeader.getSectionHeaderSize() << endl;
    cout.flush();
    elfIn.seekg(elfHeader.getSectionHeaderOffset());
    headers.resize(elfHeader.getSectionHeaderNumber());
    elfIn.read((char*)headers.data(), elfHeader.getSectionHeaderSize());

    elfSectionStringTable.reset(new ElfSectionStringTable(elfIn, getStringTableHeader()));

    cout << endl;
    cout << "Sections: " << endl;
    for(size_t i = 0; i < headers.size(); ++i)
    {
        Elf64_Shdr& header = headers[i];
        cout << elfSectionStringTable->getName(&header) << " ";
    }
    cout << endl << endl;

    for(size_t i = 0; i < headers.size(); ++i)
    {
        Elf64_Shdr& header = headers[i];
        switch(header.sh_type)
        {
		case SHT_SYMTAB:
        case SHT_DYNSYM:
			idSymTab = i; // @TODO: Verify correctness
            break;
		case SHT_STRTAB:
		    if (i != elfHeader.getSectionStringTableIndex())
		    {
		        idStrTab = i;
		        cout << "Additional SymTab at position: " << i << endl;
                additionalSymbolTables.push_back(ElfSectionStringTable(elfIn, &headers.at(i)));
                cout << endl;

                // @TODO: Load symbol table

                idSymTab = -1;
		    }
		    break;
        }
    }

    cout << "Additional SymTab types:" << endl;
    for(ElfSectionStringTable& additionalSymbolTable : additionalSymbolTables)
    {
        cout << elfSectionStringTable->getName(additionalSymbolTable.header) << " ";
    }
    cout << endl;
}

const Elf64_Shdr* ElfSectionHeader::getStringTableHeader() const
{
    return &headers.at(elfHeader.getSectionStringTableIndex());
}
