#ifndef PROCESS_H
#define PROCESS_H


#include <string>
#include <list>
#include <sys/user.h>

class Process
{
public:
    Process(const std::string& path, const std::string& name, std::list<const char*> params);
    ~Process();

    void pause();
    void cont();
    void wait();

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
