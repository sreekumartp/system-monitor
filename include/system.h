#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
public:
  std::vector<string> &Cpu();                  
  std::vector<Process> &Processes(); 
  float MemoryUtilization();         
  long UpTime();                     
  int TotalProcesses();             
  int RunningProcesses();          
  std::string Kernel();          
  std::string OperatingSystem();


private:
  int num_of_cpu_=0;
  vector<string> cpu_;
  std::vector<Process> processes_ = {};
};

#endif