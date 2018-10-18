#include "../include/PZLogger.h"
#include <iomanip>
#include <ctime>
#include <iostream>
#include <chrono>
#include <sstream>


#ifdef _IOS
#include <Foundation/Foundation.h>
#define LOG_CONSOLE(...)	NSLog(@__VA_ARGS__);
#endif

using namespace std;

PZCStr LogLevelInfo[] =
{
    "UNKNOWN",
    "DEFAULT",
    "VERBOSE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL",
    "SILENT"
    
};

PZBaseLogger::PZBaseLogger(PZ_LogPriority level):m_level(level) {}

PZBaseLogger::~PZBaseLogger() {}

time_t PZBaseLogger::GetTimePoint() 
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    return chrono::system_clock::to_time_t(now);
}

thread::id PZBaseLogger::GetThreadId() 
{
    return this_thread::get_id();
}


int PZBaseLogger::Log(PZCStr module, PZ_LogPriority level, PZCStr msg)
{
    //cout << "PZBaseLogger:" << msg << endl;
    return 0;
}

PZLoggerConsole::PZLoggerConsole(PZ_LogPriority level) : PZBaseLogger(level)
{
}

PZLoggerConsole::~PZLoggerConsole() {}
int PZLoggerConsole::Log(PZCStr module, PZ_LogPriority level, PZCStr msg)
{
    if (level > m_level)
    {
        stringstream ss;
        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);
        //auto cstime = localtime(&now_c);        

        ss << "[time:" << GetTimePoint() << "]" << "[thread:" << this_thread::get_id() << "]" << "[" << LogLevelInfo[(int)level] << "]" << msg << "\n";

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



PZLoggerFile::PZLoggerFile(PZ_LogPriority level, PZCStr filepath) : PZBaseLogger(level)
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);

    //printf("%d\n", p->tm_sec); /*获取当前秒*/
    //printf("%d\n", p->tm_min); /*获取当前分*/
    //printf("%d\n", 8 + p->tm_hour);/*获取当前时,这里获取西方的时间,刚好相差八个小时*/
    //printf("%d\n", p->tm_mday);/*获取当前月份日数,范围是1-31*/
    //printf("%d\n", 1 + p->tm_mon);/*获取当前月份,范围是0-11,所以要加1*/
    //printf("%d\n", 1900 + p->tm_year);/*获取当前年份,从1900开始，所以要加1900*/
    //printf("%d\n", p->tm_yday); /*从今年1月1日算起至今的天数，范围为0-365*/
    stringstream ss;
    ss << filepath << "/" << 1900 + p->tm_year << "-" << \
        1 + p->tm_mon << "-" << \
        p->tm_mday << "-" << \
        8 + p->tm_hour << "-" << \
        p->tm_min << "-" << p->tm_sec;
    ss << ".log";

    m_fout.open(ss.str(), ios::out);
}

PZLoggerFile::~PZLoggerFile() { m_fout.close(); }
int PZLoggerFile::Log(PZCStr module, PZ_LogPriority level, PZCStr msg)
{
    if (level > m_level)
    {
        if (m_fout.is_open()) 
        {
            if (msg) 
            {
                m_fout << "[time:" << GetTimePoint() << "]" << "[thread:" << this_thread::get_id() << "]" << "[" << LogLevelInfo[(int)level] << "]" << msg << "\n";;
            }
        }
    }

    return 0;
}

PZLoggerMix::PZLoggerMix(PZ_LogPriority level, PZCStr filename) : PZLoggerConsole(level), PZLoggerFile(level, filename)
{
    
}

PZLoggerMix::~PZLoggerMix()
{
    
}

int PZLoggerMix::Log(PZCStr module, PZ_LogPriority level, PZCStr msg)
{
    PZLoggerConsole::Log(module, level, msg);
    PZLoggerFile::Log(module, level, msg);
    return 0;
}
