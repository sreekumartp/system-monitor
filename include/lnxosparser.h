#ifndef LNX_OS_PARSE_H
#define LNX_OS_PARSE_H


#include <iostream>
#include <vector>
#include "process.h"
#include "processor.h"
using namespace std;

class LnxParser
{

public:

 vector<int> pidvect;

 vector<Process> lnxprocesses = {}; 

 vector <Process> GetProcessData();

  Processor& Cpu();                   // TODO: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          // TODO: See src/system.cpp
  long UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  std::string Kernel();               // TODO: See src/system.cpp
  std::string OperatingSystem();      // TODO: See src/system.cpp

// for system

  string GetKernel();
  string GetOS();
  long int GetUpTime();
  int GetTotalProcesses();
  int GetActiveProcesses(); 
};


#endif
