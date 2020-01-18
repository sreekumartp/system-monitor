#ifndef _OS_PARSE_H
#define _OS_PARSE_H

#include "process.h"
#include "processor.h"
#include <iostream>
#include <vector>
using namespace std;

class IOSParser {

public:

  // for process data
  virtual vector<Process> GetProcessData() = 0;

  // for system data

  virtual string GetKernel() = 0;
  virtual string GetOS() = 0;
  virtual long int GetUpTime() = 0;
  virtual int GetTotalProcesses() = 0;
  virtual int GetActiveProcesses() = 0;
  virtual float GetMemoryUtilization() = 0;
  virtual std::vector<std::string> GetCpuUtilization() = 0;
};

#endif
