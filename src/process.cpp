#include <cctype>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

void Process::SetPid(int pid) { _pid = pid; }
void Process::SetUser(string user) { _user = user; }
void Process::SetCpu(float cpu) { _cpu = cpu; }
void Process::SetRam(string ram) { _ram = ram; }
void Process::SetUpTime(long int uptime) { _uptime = uptime; }
void Process::SetCommand(string cmd) { _command = cmd; }
int Process::Pid() { return _pid; }
float Process::CpuUtilization() { return _cpu; }
string Process::Command() { return _command; }
string Process::Ram() { return _ram; }
string Process::User() { return _user; }
long int Process::UpTime() { return _uptime; }

// Overload the "less than" comparison operator for Process objects

bool Process::operator<(Process const &a[[maybe_unused]]) const { if(_pid< a._pid) return true;
else return false; }