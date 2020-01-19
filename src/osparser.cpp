#include "linux_parser.h"
#include "lnxosparser.h"

#include <iostream>
#include <vector>

using namespace std;


string OSParser::GetKernel() { return LinuxParser::Kernel(); }
string OSParser::GetOS() { return LinuxParser::OperatingSystem(); }
long int OSParser::GetUpTime() { return LinuxParser::UpTime(); }
int OSParser::GetTotalProcesses() { return LinuxParser::TotalProcesses(); }
int OSParser::GetActiveProcesses() { return LinuxParser::RunningProcesses(); }
float OSParser::GetMemoryUtilization() { return LinuxParser::MemoryUtilization();}
std::vector<std::string> OSParser::GetCpuUtilization() { return LinuxParser::CpuUtilization();}

vector<Process> OSParser::GetProcessData() {

  int pid;
  string mem;
  long int ut;
  string usr;
  string cmd;
  string uid;

  pidvect = LinuxParser::Pids();

  // cout << "OSParser:getpids() " << endl;

  // TODO: Create a vector of process objects
  // declare  variable

  // iterate through the vector of pids
  // get with pid number
  // get the cpu utilization for the pid
  // get the mem utilization for the pid
  // get the uptime for the pid
  // get the owner/user for the pids
  // get the command that create the pid

  // populate the process object with pid/cpu/mem/user/owner/uptime information
  // return the vector of objects.

  Process prcs;
  if (pidvect.size() != 0) {
    // iterate through the vector of pids
    for (size_t i = 0; i < pidvect.size(); i++) {
      // get with pid number
      pid = pidvect[i];

      // get the mem utilization for the pid
      mem = LinuxParser::Ram(pid);

      // get the uptime for the pid
      ut = LinuxParser::UpTime(pid);

      // get the owner/user for the pids
      usr = LinuxParser::User(pid);

      // get the command that create the pid
      cmd = LinuxParser::Command(pid);

      // get the cpu utilization for the pid
     /*  auto Jiff = ActiveJiffies(pid);
 */
      // get cpu usage for the pid
      float cpu_usage = LinuxParser::Cpu(pid);

      // get user id
      uid = LinuxParser::Uid(pid);

      prcs.SetPid(pid);
      prcs.SetRam(mem);
      prcs.SetCommand(cmd);
      prcs.SetCpu(cpu_usage);
      prcs.SetUser(usr);
      prcs.SetUpTime(ut);

      lnxprocesses.emplace_back(prcs);
    }


    // sort according to cpu utilization for useful display
    std::sort ( lnxprocesses.begin(), lnxprocesses.end(), 
                []( Process & a,  Process & b){

                    return (a.CpuUtilization() > b.CpuUtilization());
                    
                    }
                    
                    );
   
    
    
  }

  return lnxprocesses;
}
