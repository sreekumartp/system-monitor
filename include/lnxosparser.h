#ifndef LNX_OS_PARSE_H
#define LNX_OS_PARSE_H


#include <iostream>
#include <vector>
#include "process.h"
using namespace std;

class LnxParser
{

public:

 vector<int> pidvect;

 vector<Process> lnxprocesses = {}; 

 vector <Process> GetProcessData();



};


#endif
