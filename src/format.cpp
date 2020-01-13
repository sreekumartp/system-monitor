#include <string>

#include "format.h"
#include <sstream>
#include <iomanip>  


using std::string;
using std::stringstream;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds[[maybe_unused]]) { 
    
    int hours;
    int minutes;
    int secs;

    // seconds to hours

    hours = seconds/3600;
    minutes = (seconds - hours*3600)/60;
    secs = seconds -(hours*3600 + minutes*60);

    stringstream ss;

    ss<<std::setfill('0')<<std::setw(2)<<hours<<":"<<std::setfill('0')<<std::setw(2)<<minutes<<":"<<std::setfill('0')<<std::setw(2)<<secs;

    
    return ss.str(); 
    
}