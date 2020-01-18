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

// TODO: Return this process's ID
int Process::Pid() { return _pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return _cpu; }

// TODO: Return the command that generated this process
string Process::Command() { return _command; }

// TODO: Return this process's memory utilization
string Process::Ram() { return _ram; }

// TODO: Return the user (name) that generated this process
string Process::User() { return _user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return _uptime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &a[[maybe_unused]]) const { return true; }