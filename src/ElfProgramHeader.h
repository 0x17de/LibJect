#ifndef ELFPROGRAMHEADER_H
#define ELFPROGRAMHEADER_H


class ElfParser;
class ElfProgramHeader
{
public:
    ElfProgramHeader(ElfParser& elfParser);
    ~ElfProgramHeader();

    ElfParser& elfParser;
};

#endif // ELFPROGRAMHEADER_H
