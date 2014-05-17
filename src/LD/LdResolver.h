#ifndef LDRESOLVER_H
#define LDRESOLVER_H


class ElfParser;
class Symbol;
class Process;

class LdResolver
{
public:
    LdResolver(ElfParser& elfParser, const Process& process);
    ~LdResolver();

    void resolve(Symbol* symbol);

    const Process& process;
};

#endif // LDRESOLVER_H
