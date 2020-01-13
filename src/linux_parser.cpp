#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "format.h"

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::stringstream;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { return 0.0; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { return 0; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { 
  
stringstream ss;
string line;
string cmd="unknown";

  
  ss << pid;

  std::ifstream stream(kProcDirectory + ss.str()+ kCmdlineFilename);

  if (stream.is_open()) 
  {
      std::getline(stream, line); 
      std::istringstream linestream(line);
      linestream  >>  cmd; 
      stream.close();
       
  }


  return cmd; 
  
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) 
{ 
  
  //kProcDirectory+pid+kStatusFilename
  string line;
  string key;
  string value="0";

  stringstream ss;
  
  ss << pid;

  std::ifstream stream(kProcDirectory + ss.str()+ kStatusFilename);
  if (stream.is_open()) {

    //TODO: read lines and normalize them for easy parsing
    while (std::getline(stream, line)) 
    {

      std::replace(line.begin(), line.end(), ' ', '_');
      std::istringstream linestream(line);
      {
        if (key == "VmSize:") 
        {
          std::replace(value.begin(), value.end(), '_', ' ');
          std::replace(value.begin(), value.end(), 'k', ' ');
          std::replace(value.begin(), value.end(), 'B', ' ');


          stringstream val(value);
          stringstream ss2;
          float x=0;
          val >> x;
          x= x/1024;

          ss2 << x;
          
          auto value1=ss2.str();
         
         // std::cout << "value :" << value << std::endl; 
         stream.close();
          return value1;
        }
        else value = "0";
      }


      
    }

  }

   return value;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { 

stringstream ss;
string line;
string str1[3];

std::ifstream stream(kProcDirectory + ss.str()+ kStatusFilename);
  if (stream.is_open()) {
  
        //TODO: read lines and normalize them for easy parsing
    while (std::getline(stream, line)) 
    {
        std::istringstream linestream(line);
        linestream  >>  str1[0] >> str1[1];
        if (str1[0] == "Uid:") 
        {
          stream.close();
          return str1[1];
        }
      
    }

  }

 return str1[1];

}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) 
{ 
  
  stringstream ss;
  string line;
  string str1[3];
  string uid;
  string user="unknown";

//TODO: open /etc/<pid>/status can retrieve the UID
ss << pid;
std::ifstream stream(kProcDirectory + ss.str()+ kStatusFilename);
  if (stream.is_open()) 
  {
  
        //TODO: read lines and normalize them for easy parsing
    while (std::getline(stream, line)) 
    {
      std::replace(line.begin(), line.end(), ' ', '_');
        std::istringstream linestream(line);
        linestream  >>  str1[0] >> str1[1];
        if (str1[0] == "Uid:") 
        {
          std::replace(line.begin(), line.end(), '_', ' ');
          //UID is stored in token 2
          uid=str1[1];
          break;
        }
      
    }
    stream.close();

  }

//  TODO: open /etc/passwd and get the user corresponding to the uid.
  stream.open(kPasswordPath);
  if (stream.is_open()) 
  {

    while (std::getline(stream, line)) 
    {
     
     std::replace(line.begin(), line.end(), ':', ' ');
     std::istringstream linestream2(line);
     linestream2  >>  str1[0] >> str1[1] >> str1[2];
      if (str1[2] == uid) 
      {
        user=str1[0];
        stream.close();
        return user;
      }
    }

  }

 return user;
    
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid[[maybe_unused]]) 
{ 

stringstream ss;
string line;
string value;
long int ut=0;

string str1[23];
  
  
  ss << pid;

  std::ifstream stream(kProcDirectory + ss.str()+ kStatFilename);
  if (stream.is_open()) {
  
        //TODO: read lines and normalize them for easy parsing
    while (std::getline(stream, line)) 
    {
     
      std::istringstream linestream(line);
      linestream  >>  str1[0] >> str1[1] >> str1[2] >> str1[3] >> str1[4] >> str1[5] >> str1[6] >> str1[7] >> str1[8] >> \
      str1[9] >> str1[10] >> str1[11] >> str1[12] >> str1[13] >> str1[14] >> str1[15] >> \
      str1[16] >> str1[17] >> str1[18] >> str1[19] >> \
      str1[20] >> str1[21] >> str1[22] ;

      ut = std::stol(str1[21], nullptr, 10);
      ut = ut / sysconf(_SC_CLK_TCK);

        Format::ElapsedTime(ut);
      //stringstream val(str1[22]);  
          //val >> ut;
        stream.close();
        return ut;
    }
  
  
  }

return ut; 

}


/*
To calculate CPU usage for a specific process you'll need the following:

/proc/uptime
#1 uptime of the system (seconds)
/proc/[PID]/stat
#14 utime - CPU time spent in user code, measured in clock ticks
#15 stime - CPU time spent in kernel code, measured in clock ticks
#16 cutime - Waited-for children's CPU time spent in user code (in clock ticks)
#17 cstime - Waited-for children's CPU time spent in kernel code (in clock ticks)
#22 starttime - Time when the process started, measured in clock ticks
Hertz (number of clock ticks per second) of your system.
In most cases, getconf CLK_TCK can be used to return the number of clock ticks.
The sysconf(_SC_CLK_TCK) C function call may also be used to return the hertz value.
*/

/*

Calculation
First we determine the total time spent for the process:

total_time = utime + stime
We also have to decide whether we want to include the time from children processes. If we do, then we add those values to total_time:

total_time = total_time + cutime + cstime
Next we get the total elapsed time in seconds since the process started:

seconds = uptime - (starttime / Hertz)
Finally we calculate the CPU usage percentage:

cpu_usage = 100 * ((total_time / Hertz) / seconds)

*/

float LinuxParser::Cpu(int pid)
{

stringstream ss;
string line;
string value;
string str1[23];
//TODO: get uptime

float uptime=0.0;
float p_utime=0.0;
float p_stime=0.0;
float p_cutime=0.0;
float p_cstime=0.0;
float p_starttime=0.0;
float cpu_usage=0.0;

std::ifstream stream("/proc/uptime");
 if (stream.is_open()) 
 {
  while (std::getline(stream, line)) 
    {
      std::istringstream linestream(line);
      linestream  >>  str1[0] >> str1[1];
      uptime= std::stof(str1[0],nullptr); 
      stream.close();
      break;
    }
 }

  ss << pid;

  stream.open(kProcDirectory + ss.str()+ kStatFilename);
  if (stream.is_open()) 
  {  
      std::getline(stream, line); 
      std::istringstream linestream(line);
      linestream  >>  str1[0] >> str1[1] >> str1[2] >> str1[3] >> str1[4] >> str1[5] >> str1[6] >> str1[7] >> str1[8] >> \
      str1[9] >> str1[10] >> str1[11] >> str1[12] >> str1[13] >> str1[14] >> str1[15] >> \
      str1[16] >> str1[17] >> str1[18] >> str1[19] >> \
      str1[20] >> str1[21] >> str1[22] ;

      p_utime=std::stof(str1[13],nullptr);
      p_stime=std::stof(str1[14],nullptr); 
      p_cutime=std::stof(str1[15],nullptr);
      p_cstime=std::stof(str1[16],nullptr);
      p_starttime=std::stof(str1[21],nullptr);

      auto total_time= p_utime+p_stime;
      total_time = total_time+ p_cutime + p_cstime;
      
      //seconds = uptime - (starttime / Hertz)
      auto seconds = uptime - (p_starttime/sysconf(_SC_CLK_TCK));
    
      //cpu_usage = 100 * ((total_time / Hertz) / seconds)
      
      cpu_usage = 100 * ((total_time / sysconf(_SC_CLK_TCK))/seconds);
    
  }

  return cpu_usage;

}





