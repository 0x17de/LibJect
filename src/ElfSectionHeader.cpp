#include <iostream>
#include <fstream>
#include "ElfParser.h"
#include "ElfHeader.h"
#include "ElfSectionHeader.h"
#include "ElfSymbolTable.h"
#include "SymbolTable.h"

using namespace std;

ElfSectionHeader::ElfSectionHeader(ElfParser& elfParser)
:
    elfParser(elfParser),
    idSymTab(-1),
    idStrTab(-1)
{
    ElfHeader& elfHeader = *elfParser.elfHeader.get();
    ifstream& elfIn = elfParser.elfIn;

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
}

ElfSectionHeader::~ElfSectionHeader()
{
}

void ElfSectionHeader::readSymbolTable(SymbolTable& symbolTable)
{
    ElfHeader& elfHeader = *elfParser.elfHeader.get();
    ifstream& elfIn = elfParser.elfIn;

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
                ElfSymbolTable elfSymbolTable(elfIn, &headers.at(idSymTab));
                ElfSectionStringTable elfStringTable(elfIn, &headers.at(i));

                symbolTable.read(elfSymbolTable, elfStringTable);

                idSymTab = -1;
            }
            break;
        }
    }
}

const Elf64_Shdr* ElfSectionHeader::getStringTableHeader() const
{
    return &headers.at(elfParser.elfHeader->getSectionStringTableIndex());
}
