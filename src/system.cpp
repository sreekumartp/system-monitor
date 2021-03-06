#include <cstddef>
#include <set>
#include <string>
#include <unistd.h>
#include <vector>

#include "lnxosparser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;


// TODO: Return the system's CPU
vector<string> &System::Cpu() {

 

  OSParser lp;

   cpu_ = lp.GetCpuUtilization();
  

  return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process> &System::Processes() {

  // todo: fill a vector of process objects
  // todo : get the process object
  // todo : add to the vector
  // toco : fill until no more process obejects left.
  // todo : create the object here of call another function that returns the
  // objects?

  OSParser lp;

  processes_ = lp.GetProcessData();

  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {

  OSParser lp;

  string kernel_name = lp.GetKernel();

  return kernel_name;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {
  OSParser lp;

  return lp.GetMemoryUtilization();
}

// TODO: Return the operating system name
std::string System::OperatingSystem() {

  OSParser lp;

  return lp.GetOS();
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {

  OSParser lp;

  return lp.GetActiveProcesses();
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {

  OSParser lp;

  return lp.GetTotalProcesses();
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() {

  OSParser lp;

  return lp.GetUpTime();
}