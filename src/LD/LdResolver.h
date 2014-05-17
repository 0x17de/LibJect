#ifndef LDRESOLVER_H
#define LDRESOLVER_H


#include <memory>

class ElfParser;
class Symbol;
class Process;
class ProcMap;

class LdResolver
{
public:
    LdResolver(ElfParser& elfParser, const Process& process);
    ~LdResolver();

    bool resolve(const std::string& libname, Symbol* symbol);

    const Process& process;
    std::unique_ptr<ProcMap> procMap;
};

#endif // LDRESOLVER_H
