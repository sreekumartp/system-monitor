#ifndef PROCESS_H
#define PROCESS_H

#include <string>

using namespace std;
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
public:
  int Pid();                              
  std::string User();                     
  std::string Command();                
  float CpuUtilization();                 
  std::string Ram();                     
  long int UpTime();                      
  bool operator<(Process const &a) const; 

  void SetPid(int pid);
  void SetUser(string user);
  void SetCpu(float cpu);
  void SetRam(string ram);
  void SetUpTime(long int uptime);
  void SetCommand(string cmd);
  void SetUid(int pid);
  string GetUid() { return _uid; }
  Process() {

    _pid = 0;
    _user = "user";
    _command = "cmd";
    _cpu = 99.98;
    _ram = "full";
    _uptime = 65535;
    _uid = "uid";
  }
  // TODO: Declare any necessary private members
private:
  int _pid;
  string _user;
  string _command;
  float _cpu;
  string _ram;
  long int _uptime;
  string _uid;
};

#endif