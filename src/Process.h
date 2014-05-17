#ifndef PROCESS_H
#define PROCESS_H


#include <string>
#include <list>
#include <sys/user.h>

struct Breakpoint
{
    Breakpoint(size_t address, char byte);
    size_t address;
    char byte;
};

union size_char_t
{
    size_t l;
    char c[sizeof(size_t)];
};

class Process
{
public:
    Process(const std::string& path, const std::string& name, std::list<const char*> params, std::list<const char*> envs);
    ~Process();

    void pause();
    void cont();
    void wait();

    Breakpoint breakAt(size_t address);
    void removeBreakpoint(Breakpoint breakpoint);

    void saveRegs();
    void restoreRegs();
    user_regs_struct getRegs();
    void setRegs(user_regs_struct s);

    void backupStack(size_t size);
    void restoreStack();

    std::string name;
    pid_t pid;
    user_regs_struct regs;

    size_t stackBackupRSP;
    std::vector<size_t> stackBackup;
};

#endif // PROCESS_H
