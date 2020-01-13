#include <iostream>

#include "lnxosparser.h"
#include "linux_parser.h"
#include "process.h"
#include <vector>

using namespace std;
using namespace LinuxParser;



    vector <Process> LnxParser::GetProcessData()
    {

      pidvect= Pids();

      //cout << "LnxParser:getpids() " << endl;

      //TODO: Create a vector of process objects
      // declare  variable


      // iterate through the vector of pids
      // get with pid number
      // get the cpu utilization for the pid 
      // get the mem utilization for the pid 
      // get the uptime for the pid 
      // get the owner/user for the pids 
      // get the command that create the pid
       
      // populate the process object with pid/cpu/mem/user/owner/uptime information
      // return the vector of objects.

      Process prcs;
      if(pidvect.size() !=0)
      {
        // iterate through the vector of pids
        for(size_t i = 0; i < pidvect.size() ;i++)
        {
          // get with pid number
          auto pid = pidvect[i];
         
          // get the mem utilization for the pid 
          auto mem = Ram(pid);
         

          // get the uptime for the pid 
          auto ut = UpTime(pid);
         

          // get the owner/user for the pids 
          auto usr = User(pid);
       

          // get the command that create the pid
          auto cmd = Command(pid);
        

          // get the cpu utilization for the pid 
          auto Jiff = ActiveJiffies(pid);
    

          prcs.SetPid(pid);
          prcs.SetRam(mem);
          prcs.SetCommand(cmd);
          prcs.SetCpu(Jiff);
          prcs.SetUser(usr);
          prcs.SetUpTime(ut);
          
          lnxprocesses.push_back(prcs);

        }
      }

      return lnxprocesses;
    }


