#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>

using namespace std;

class Processor {
public:
  float Utilization(); // TODO: See src/processor.cpp
  void SetUtlization(string util);
  // TODO: Declare any necessary private members
private:
  string utilization_;
};

#endif