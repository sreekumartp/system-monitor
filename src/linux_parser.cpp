#include "format.h"
#include <dirent.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <iomanip>
#include "linux_parser.h"

using std::stof;
using std::stol;
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
  string version;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR *directory = opendir(kProcDirectory.c_str());
  struct dirent *file;
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

//  Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {

  string line, key, value;
  string total, free;
  float memtotal = 0.0, memfree = 0.0;

  std::ifstream stream(kProcDirectory + kMeminfoFilename);

  if (stream.is_open()) {

    while (std::getline(stream, line)) {

      std::istringstream linestream(line);

      linestream >> key >> value;

      if (key == "MemTotal:") {
        total = value;
        memtotal = std::stof(total, nullptr);

      } else if (key == "MemFree:") {
        free = value;
        memfree = std::stof(free, nullptr);
      }
      // TODO: Optimization :could break after retrieving Memtotal & MemFree,but
      // we will just let the loop run through to exit
    }

    stream.close();
  }

  return ((memtotal - memfree) / memtotal);
}

//  Read and return the system uptime
long LinuxParser::UpTime() {

  long int utime;
  string line;
  string uptime;
  string idletime;

  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {

    // read lines and normalize them for easy parsing
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idletime;
    utime = std::stol(uptime, nullptr, 10);
    stream.close();
  }

  return utime;
}

// TODO:Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {

  string user;
  string nice;
  string system;
  string idle;
  string iowait;
  string irq;
  string softirq;
  string steal;
  string guest;
  string guest_nice;

  stringstream ss;
  string line;
  string cpuid;
  float util=0.00;
  float total_time=0.00;

  long num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
  vector<string> cpu(num_cpus+1, "0");
  long count = 0;

  std::ifstream stream(kProcDirectory + kStatFilename);

  if (stream.is_open()) {

  

    while (std::getline(stream, line) && count < num_cpus+1) {
      std::istringstream linestream(line);
      linestream >> cpuid >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

   
      total_time = stof(nice, nullptr);
      total_time += stof(system, nullptr);
      total_time += stof(idle, nullptr);
      total_time += stof(iowait, nullptr);
      total_time += stof(irq, nullptr);
      total_time += stof(softirq, nullptr);
      total_time += stof(steal, nullptr);
  

      float idle_time = stof(idle, nullptr);
    
      util = (total_time - idle_time )/ total_time;

      std::ostringstream ss;
      ss << util;
     
      cpu[count] = ss.str();
      count++;
    }
    stream.close();
    return cpu;
  }

  return cpu;
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  vector<int> vect_of_pids;

  vect_of_pids = Pids();

  return vect_of_pids.size();
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() {

  stringstream ss;
  string key;
  string value;
  string line;
  int ActiveProcess = 0;
  // first get list of process.

  vector<int> vect_of_pids;

  int num_of_pids = vect_of_pids.size();

  // TODO: modify this to iteratot of C++11 standard
  for (int i = 0; i < num_of_pids; i++) {
    ss << vect_of_pids[i];

    std::ifstream stream(kProcDirectory + ss.str() + kStatusFilename);
    if (stream.is_open()) {

      while (std::getline(stream, line)) {
        std::istringstream linestream(line);
        linestream >> key >> value;

        if (key == "State:") {
          if (value == "R") {
            ActiveProcess++;
          }

          stream.close();
          break;
        }
      }
    }
  }
  return ActiveProcess;
}

// Read and return the command associated with a process

string LinuxParser::Command(int pid[[maybe_unused]]) {

  stringstream ss;
  string line;
  string cmd = "unknown";

  ss << pid;

  std::ifstream stream(kProcDirectory + ss.str() + kCmdlineFilename);

  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cmd;
    stream.close();
  }

  return cmd;
}

// Read and return the memory used by a process

string LinuxParser::Ram(int pid) {

  string line;
  string key;
  string value = "0";

  stringstream ss;

  ss << pid;

  std::ifstream stream(kProcDirectory + ss.str() + kStatusFilename);
  if (stream.is_open()) {

    // read lines and normalize them for easy parsing
    while (std::getline(stream, line)) {

      std::replace(line.begin(), line.end(), ' ', '_');
      std::istringstream linestream(line);
      linestream >> key >> value;

      if (key == "VmSize:") {
        std::replace(value.begin(), value.end(), '_', ' ');
        std::replace(value.begin(), value.end(), 'k', ' ');
        std::replace(value.begin(), value.end(), 'B', ' ');

        stringstream val(value);
        stringstream ss2;
        float x = 0.00;

        x = stof(val.str(), nullptr);
        x = x / 1024;
        ss2 << std::fixed << std::setprecision(2)<< x;

        auto value1 = ss2.str();

        // std::cout << "value :" << value << std::endl;
        stream.close();
        return value1;
      } else
        value = "0";
    }
  }

  return value;
}

// Read and return the user ID associated with a process

string LinuxParser::Uid(int pid[[maybe_unused]]) {

  stringstream ss;
  string line;
  string str1[3];

  std::ifstream stream(kProcDirectory + ss.str() + kStatusFilename);
  if (stream.is_open()) {

    // read lines and normalize them for easy parsing
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> str1[0] >> str1[1];
      if (str1[0] == "Uid:") {
        stream.close();
        return str1[1];
      }
    }
  }

  return str1[1];
}

// Read and return the user associated with a process

string LinuxParser::User(int pid[[maybe_unused]]) {

  stringstream ss;
  string line;
  string str1[3];
  string uid;
  string user = "unknown";

  // open /etc/<pid>/status can retrieve the UID
  ss << pid;
  std::ifstream stream(kProcDirectory + ss.str() + kStatusFilename);
  if (stream.is_open()) {

    // TODO: read lines and normalize them for easy parsing
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::istringstream linestream(line);
      linestream >> str1[0] >> str1[1];
      if (str1[0] == "Uid:") {
        std::replace(line.begin(), line.end(), '_', ' ');
        // UID is stored in token 2
        uid = str1[1];
        break;
      }
    }
    stream.close();
  }

  //  open /etc/passwd and get the user corresponding to the uid.
  stream.open(kPasswordPath);
  if (stream.is_open()) {

    while (std::getline(stream, line)) {

      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream2(line);
      linestream2 >> str1[0] >> str1[1] >> str1[2];
      if (str1[2] == uid) {
        user = str1[0];
        stream.close();
        return user;
      }
    }
  }

  return user;
}

// Read and return the uptime of a process

long int LinuxParser::UpTime(int pid) {

  stringstream ss;
  string line;
  string value;
  long int ut = 0;

  string str1[23];

  ss << pid;

  std::ifstream stream(kProcDirectory + ss.str() + kStatFilename);
  if (stream.is_open()) {

    // read lines and normalize them for easy parsing
    while (std::getline(stream, line)) {

      std::istringstream linestream(line);
      linestream >> str1[0] >> str1[1] >> str1[2] >> str1[3] >> str1[4] >>
          str1[5] >> str1[6] >> str1[7] >> str1[8] >> str1[9] >> str1[10] >>
          str1[11] >> str1[12] >> str1[13] >> str1[14] >> str1[15] >>
          str1[16] >> str1[17] >> str1[18] >> str1[19] >> str1[20] >>
          str1[21] >> str1[22];

      ut = std::stol(str1[21], nullptr, 10);
      ut = ut / sysconf(_SC_CLK_TCK);

      Format::ElapsedTime(ut);
      // stringstream val(str1[22]);
      // val >> ut;
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
#17 cstime - Waited-for children's CPU time spent in kernel code (in clock
ticks)
#22 starttime - Time when the process started, measured in clock ticks
Hertz (number of clock ticks per second) of your system.
In most cases, getconf CLK_TCK can be used to return the number of clock ticks.
The sysconf(_SC_CLK_TCK) C function call may also be used to return the hertz
value.
*/

/*

Calculation
First we determine the total time spent for the process:

total_time = utime + stime
We also have to decide whether we want to include the time from children
processes. If we do, then we add those values to total_time:

total_time = total_time + cutime + cstime
Next we get the total elapsed time in seconds since the process started:

seconds = uptime - (starttime / Hertz)
Finally we calculate the CPU usage percentage:

cpu_usage = 100 * ((total_time / Hertz) / seconds)

*/

float LinuxParser::Cpu(int pid) {

  stringstream ss;
  string line;
  string value;
  string str1[53];

  long ticks_per_sec = 0;
  float uptime = 0.00;
  long p_utime = 0;
  long p_stime = 0;
  long p_cutime = 0;
  long p_cstime = 0;
  long p_starttime = 0;
  long total_time = 0;
  float cpu_usage = 0.0;

  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);

    std::istringstream linestream(line);
    linestream >> str1[0] >> str1[1];
    uptime = std::stof(str1[0], nullptr);
    stream.close();
  }

  ss << pid;

  stream.open(kProcDirectory + ss.str() + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> str1[0] >> str1[1] >> str1[2] >> str1[3] >> str1[4] >>
        str1[5] >> str1[6] >> str1[7] >> str1[8] >> str1[9] >> str1[10] >>
        str1[11] >> str1[12] >> str1[13] >> str1[14] >> str1[15] >> str1[16] >>
        str1[17] >> str1[18] >> str1[19] >> str1[20] >> str1[21] >> str1[22] >>
        str1[23] >> str1[24] >> str1[25] >> str1[26] >> str1[27] >> str1[28] >>
        str1[29] >> str1[30] >> str1[31] >> str1[32] >> str1[33] >> str1[34] >>
        str1[35] >> str1[36] >> str1[37] >> str1[38] >> str1[39] >> str1[40] >>
        str1[41] >> str1[42] >> str1[43] >> str1[44] >> str1[45] >> str1[46] >>
        str1[47] >> str1[48] >> str1[49] >> str1[50] >> str1[51];

    p_utime = std::stol(str1[13], nullptr,10);
    p_stime = std::stol(str1[14], nullptr,10);
    p_cutime = std::stol(str1[15], nullptr,10);
    p_cstime = std::stol(str1[16], nullptr,10);
    p_starttime = std::stol(str1[21], nullptr,10);

    total_time = p_utime + p_stime;
    total_time = total_time + p_cutime + p_cstime;
   

    ticks_per_sec = sysconf(_SC_CLK_TCK);
    float secs = (uptime - (p_starttime / ticks_per_sec));
    cpu_usage =  ((total_time / ticks_per_sec) / secs);
  
  }

  return cpu_usage;
}
