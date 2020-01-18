#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "lnxosparser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    
  //todo: fill a vector of process objects 
  //todo : get the process object
  //todo : add to the vector
  //toco : fill until no more process obejects left.
  //todo : create the object here of call another function that returns the objects?
    
    LnxParser lp;


    processes_=lp.GetProcessData();
    
    return processes_;
    
    
     }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 

   
    LnxParser lp;

    string kernel_name = lp.GetKernel();
  
  return kernel_name; 
  }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return 0.0; }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 

   LnxParser lp;
  
  return lp.GetOS(); 
  }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
  
  LnxParser lp;

  return lp.GetActiveProcesses(); 

}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
  
  LnxParser lp;

  return lp.GetTotalProcesses(); 

  }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 

  LnxParser lp;
  
  return lp.GetUpTime();

}