#include <iostream>
#include <fstream>
#include "ElfProgramHeader.h"
#include "ElfParser.h"
#include "ElfHeader.h"

using namespace std;

ElfProgramHeader::ElfProgramHeader(ElfParser& elfParser)
:
    elfParser(elfParser)
{
    ElfHeader& elfHeader = *elfParser.elfHeader.get();
    ifstream& elfIn = elfParser.elfIn;

    cout << "Program header location: 0x" << hex << elfHeader.getProgramHeaderOffset() << ", Size: " << dec << elfHeader.getProgramHeaderSize() << endl;
    cout.flush();

    int numberOfProgramEntries = elfHeader.getProgramHeaderNumber();

    elfIn.seekg(elfHeader.getProgramHeaderOffset());
    headers.resize(numberOfProgramEntries);
    elfIn.read((char*)headers.data(), elfHeader.getProgramHeaderSize());

    for(int i = 0; i < numberOfProgramEntries; ++i)
    {
        Elf64_Phdr& header = headers.at(i);
        switch(header.p_type)
        {
        case PT_INTERP:
        {
            int pathStringSize = header.p_filesz;
            if (header.p_filesz == 0)
                break;

            std::vector<char> pathData;
            pathData.resize(pathStringSize);
            elfIn.seekg(header.p_offset);
            elfIn.read(pathData.data(), pathStringSize);
            interpreterPath = string(pathData.data());

            cout << "PT_INTERP: " << interpreterPath << ", virtual: 0x";
            cout.width(sizeof(size_t));
            cout.fill('0');
            cout << hex << header.p_vaddr << endl;
            break;
        }
        case PT_DYNAMIC:
            cout << "PT_DYNAMIC: 0x";
            cout.width(sizeof(size_t));
            cout.fill('0');
            cout << hex << header.p_offset;
            cout << ", virtual: 0x";
            cout.width(sizeof(size_t));
            cout.fill('0');
            cout << hex << header.p_vaddr << endl;
            break;
        case PT_LOAD:
            cout << "PT_LOAD:    0x";
            cout.width(sizeof(size_t));
            cout.fill('0');
            cout << hex << header.p_offset;
            cout << ", virtual: 0x";
            cout.width(sizeof(size_t));
            cout.fill('0');
            cout << hex << header.p_vaddr << endl;
            break;
        }
    }

    cout << endl;
}

ElfProgramHeader::~ElfProgramHeader()
{
}
