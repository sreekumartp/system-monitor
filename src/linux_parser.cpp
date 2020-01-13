#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

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
string LinuxParser::Command(int pid[[maybe_unused]]) { return "cmd"; }

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
      while (linestream >> key >> value) 
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
  
  return "sree";

}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return "sree"; }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid[[maybe_unused]]) 
{ 

stringstream ss;
string line;
string value;
long int ut;

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

      stringstream val(str1[22]);  
          val >> ut;
          return ut;
    }
  
  
  }

return ut; 

}