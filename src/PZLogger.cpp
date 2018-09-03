#include "../include/PZLogger.h"
#include <iomanip>
#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

#ifdef _IOS
#include <Foundation/Foundation.h>
#define LOG_CONSOLE(...)	NSLog(@__VA_ARGS__);
#endif

using namespace std;

PZCStr LogLevelInfo[] = { "UNKNOWN", "DEFAULT", "VERBOSE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL", "SILENT" };

PZBaseLogger::PZBaseLogger(PZ_LogPriority level):m_level(level) {}

PZBaseLogger::~PZBaseLogger() {}


int PZBaseLogger::Log(PZCStr module, PZ_LogPriority level, PZCStr msg)
{
    cout << "PZBaseLogger:" << msg << endl;
    return 0;
}

PZLogger::PZLogger(PZ_LogPriority level) : PZBaseLogger(level)
{
}

PZLogger::~PZLogger() {}
int PZLogger::Log(PZCStr module, PZ_LogPriority level, PZCStr msg)
{
    if (level > m_level)
    {
        stringstream ss;
        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);
        //auto cstime = localtime(&now_c);        

        ss << "[time:" << now_c << "]" << "[thread:" << this_thread::get_id() << "]" << "[" << LogLevelInfo[(int)level] << "]" << msg << "\n";

        fprintf(stdout, "%s", ss.str().c_str());

//#ifdef _WINDOWS
//        fprintf(stdout, "%s", ss.str().c_str());
//#elif ANDROID
//        __android_log_print(level, "PZLOG-", "%s", ss.str().c_str());
//#elif _IOS
//        LOG_CONSOLE("%s", ss.str().c_str());
//#endif
        
    }
    
    return 0;
}