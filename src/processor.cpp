#include <string>
#include "processor.h"
using namespace std;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
 { 
   
    float util=0.0;

    util=std::stof(utilization_,nullptr);
    
    return util;

  }
  void Processor:: SetUtlization(string util) {  utilization_ = util;}