#include <iostream>

#include "lnxosparser.h"
#include "linux_parser.h"
#include "process.h"
#include <vector>

using namespace std;
using namespace LinuxParser;


    string LnxParser::GetKernel()
    {
      return LinuxParser::Kernel();
      
    }
    string LnxParser::GetOS()
    {
      return LinuxParser::OperatingSystem();
      
    }

    long int LnxParser::GetUpTime()
    {

      return LinuxParser::UpTime();

    }

    int LnxParser::GetTotalProcesses()
    {

      return LinuxParser::TotalProcesses();

    }

    int LnxParser::GetActiveProcesses()
    {

      
        return LinuxParser::RunningProcesses();
    }

    float LnxParser::GetMemoryUtilization()
    {

      return LinuxParser::MemoryUtilization();
    }




    vector <Process> LnxParser::GetProcessData()
    {

      int pid;
      string mem;
      long int ut;
      string usr;
      string cmd;
      float cpu;
      string uid;

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
           pid = pidvect[i];
         
          // get the mem utilization for the pid 
           mem = Ram(pid);
         

          // get the uptime for the pid 
           ut =  LinuxParser::UpTime(pid);
         

          // get the owner/user for the pids 
           usr =  LinuxParser::User(pid);
       

          // get the command that create the pid
           cmd = Command(pid);
        

          // get the cpu utilization for the pid 
          auto Jiff = ActiveJiffies(pid);
          
          //get cpu usage for the pid
          float cpu_usage =  LinuxParser::Cpu(pid);
    
          //get user id
          uid = Uid(pid);

          prcs.SetPid(pid);
          prcs.SetRam(mem);
          prcs.SetCommand(cmd);
          prcs.SetCpu(cpu_usage);
          prcs.SetUser(usr);
          prcs.SetUpTime(ut);
                    
          lnxprocesses.emplace_back(prcs);

        }

            reverse(lnxprocesses.begin(), lnxprocesses.end()); 
      }

      return lnxprocesses;
    }


