#ifndef LNX_OS_PARSE_H
#define LNX_OS_PARSE_H

#include "IOSparser.h"
#include "process.h"
#include "processor.h"
#include <iostream>
#include <vector>
using namespace std;

class OSParser : public IOSParser {

public:
  vector<int> pidvect;

  vector<Process> lnxprocesses = {};

// for process data
  virtual vector<Process> GetProcessData() override;

  // for system data

  virtual string GetKernel() override;
  virtual string GetOS() override;
  virtual long int GetUpTime() override;
  virtual int GetTotalProcesses() override;
  virtual int GetActiveProcesses() override;
  virtual float GetMemoryUtilization() override;
  virtual std::vector<std::string> GetCpuUtilization() override;
};

#endif
