#ifndef ELFPROGRAMHEADER_H
#define ELFPROGRAMHEADER_H


#include <elf.h>
#include <vector>

class ElfParser;
class ElfProgramHeader
{
public:
    ElfProgramHeader(ElfParser& elfParser);
    ~ElfProgramHeader();

    ElfParser& elfParser;
    std::string getInterpreterPath();

private:
    std::vector<Elf64_Phdr> headers;
    std::string interpreterPath;
};

#endif // ELFPROGRAMHEADER_H
