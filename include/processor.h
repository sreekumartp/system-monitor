#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>

using namespace std;

class Processor {
public:
  float Utilization(); 
  void SetUtlization(string util);
 
private:
  string utilization_;
};

#endif