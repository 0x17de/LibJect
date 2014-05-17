#include <iostream>

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include "Process.h"

using namespace std;

Breakpoint::Breakpoint(size_t address, char byte)
:
    address(address),
    byte(byte)
{
}

Process::Process(const std::string& path, const std::string& name, std::list<const char*> params, std::list<const char*> envs)
:
    name(name)
{
    pid = fork();
    if (pid == 0)
    {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        vector<const char*> execParams, execEnvs;
        execParams.push_back("name");
        execParams.insert(execParams.end(), params.begin(), params.end());
        execParams.push_back(0);
        execEnvs.insert(execEnvs.end(), envs.begin(), envs.end());
        execEnvs.push_back(0);
        execve(path.c_str(), const_cast<char* const*>(execParams.data()), const_cast<char* const*>(execEnvs.data()));
    }
    else
    {
        ::wait(0);
    }
}

void Process::saveRegs()
{
    regs = getRegs();
}

void Process::restoreRegs()
{
    setRegs(regs);
}

user_regs_struct Process::getRegs()
{
    user_regs_struct ret;
    ptrace(PTRACE_GETREGS, pid, 0, &ret);
    return ret;
}

void Process::setRegs(user_regs_struct s)
{
    ptrace(PTRACE_GETREGS, pid, 0, &s);
}

Breakpoint Process::breakAt(size_t address)
{
    size_char_t data;
    data.l = ptrace(PTRACE_PEEKDATA, pid, address, 0);

    Breakpoint breakpoint(address, data.c[0]);
    cout << "Breakpoint at 0x" << hex << address << ", byte was: " << (int)(data.c[0] & 0xFF) << endl;
    data.c[0] = 0xCC;
    ptrace(PTRACE_POKEDATA, pid, address, data.l);

    return breakpoint;
}

void Process::removeBreakpoint(Breakpoint breakpoint)
{
    size_char_t data;
    data.l = ptrace(PTRACE_PEEKDATA, pid, breakpoint.address, 0);
    cout << "Remove breakpoint at 0x" << hex << breakpoint.address << ", byte: " << (int)(data.c[0] & 0xFF) << endl;
    data.c[0] = breakpoint.byte;
    ptrace(PTRACE_POKEDATA, pid, breakpoint.address, data.l);
}

void Process::backupStack(size_t size)
{
    auto r = getRegs();
    stackBackupRSP = r.rsp;
    stackBackup.resize(size);
    for(size_t i = 0; i < size; ++i)
    {
        stackBackup[i] = ptrace(PTRACE_PEEKDATA, pid, stackBackupRSP + i * sizeof(size_t), 0);
    }
}

void Process::restoreStack()
{
    for(size_t i = 0; i < stackBackup.size(); ++i)
    {
        ptrace(PTRACE_POKEDATA, pid, stackBackupRSP + i * sizeof(size_t), stackBackup[i]);
    }
    auto r = getRegs();
    r.rsp = stackBackupRSP;
    setRegs(r);
}

void Process::pause()
{
    kill(pid, SIGSTOP);
}

void Process::cont()
{
    ptrace(PTRACE_CONT, pid, 0, 0);
}

void Process::wait()
{
    waitpid(pid, 0, 0);
}

Process::~Process()
{
}
