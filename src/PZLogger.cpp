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

time_t GetTimePoint()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();
    return chrono::system_clock::to_time_t(now);
}

thread::id GetThreadId()
{
    return this_thread::get_id();
}

string format_msg(PZCStr module, PZ_LogPriority level, PZCStr msg)
{
    stringstream ss;
    ss << "[module:" << module << "]" << "[time:" << GetTimePoint() << "]" << "[thread:" << this_thread::get_id() << "]" << "[" << LogLevelInfo[(int)level] << "]" << msg << "\n";
    return ss.str();
}

PZBaseLogger::PZBaseLogger(PZ_LogPriority level):m_level(level) {}

PZBaseLogger::~PZBaseLogger() {}




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
        
        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);
        //auto cstime = localtime(&now_c);

        fprintf(stdout, "%s", format_msg(module, level, msg).c_str());

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
                m_fout << format_msg(module, level, msg) << endl;
            }
        }
    }

    return 0;
}

PZLoggerMix::PZLoggerMix(PZ_LogPriority level, PZCStr filename) : PZBaseLogger(level),
                                                                    m_console_log(new PZLoggerConsole(level)),
                                                                    m_file_log(new PZLoggerFile(level, filename))
{

}

PZLoggerMix::~PZLoggerMix()
{
    
}

int PZLoggerMix::Log(PZCStr module, PZ_LogPriority level, PZCStr msg)
{
    m_console_log->Log(module, level, msg);
    m_file_log->Log(module, level, msg);
    return 0;
}

PZLoggerNetWork::PZLoggerNetWork(PZ_LogPriority level, PZCStr filename) : PZBaseLogger(level)
{
    stringstream ss;
    string addr = filename;
    size_t pos = addr.find(":");
    
    ss << addr.substr(0, pos);
    string ip;
    ss >> ip;
    ss.clear();
    ss.str("");
    
    int port = 0;
    ss << addr.substr(pos+1, addr.length() - ip.length());
    ss >> port;
    m_socket = new LSocket(ip, port);
    
    
}

PZLoggerNetWork::~PZLoggerNetWork()
{
    delete m_socket;
}

int PZLoggerNetWork::Log(PZCStr module, PZ_LogPriority level, PZCStr msg)
{
    string msg_ = format_msg(module, level, msg);
    m_socket->send(msg_.c_str(), msg_.length());
    return 0;
}
