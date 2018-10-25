#include "../include/LLLogger.h"
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

LLCStr LogLevelInfo[] =
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

string format_msg(LLCStr module, LL_LogPriority level, LLCStr msg)
{
    stringstream ss;
    ss << "[module:" << module << "]" << "[time:" << GetTimePoint() << "]" << "[thread:" << this_thread::get_id() << "]" << "[" << LogLevelInfo[(int)level] << "]" << msg << "\n";
    return ss.str();
}

LLBaseLogger::LLBaseLogger(LL_LogPriority level):m_level(level) {}

LLBaseLogger::~LLBaseLogger() {}




int LLBaseLogger::Log(LLCStr module, LL_LogPriority level, LLCStr msg)
{
    //cout << "LLBaseLogger:" << msg << endl;
    return 0;
}

LLLoggerConsole::LLLoggerConsole(LL_LogPriority level) : LLBaseLogger(level)
{
}

LLLoggerConsole::~LLLoggerConsole() {}
int LLLoggerConsole::Log(LLCStr module, LL_LogPriority level, LLCStr msg)
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
//        __android_log_print(level, "LLLOG-", "%s", ss.str().c_str());
//#elif _IOS
//        LOG_CONSOLE("%s", ss.str().c_str());
//#endif
        
    }
    
    return 0;
}



LLLoggerFile::LLLoggerFile(LL_LogPriority level, LLCStr filepath) : LLBaseLogger(level)
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);

    //printf("%d\n", p->tm_sec); /*ȡǰ*/
    //printf("%d\n", p->tm_min); /*ȡǰ*/
    //printf("%d\n", 8 + p->tm_hour);/*ȡǰʱ,ȡʱ,պ˸Сʱ*/
    //printf("%d\n", p->tm_mday);/*ȡǰ·,Χ1-31*/
    //printf("%d\n", 1 + p->tm_mon);/*ȡǰ·,Χ0-11,Ҫ1*/
    //printf("%d\n", 1900 + p->tm_year);/*ȡǰ,1900ʼҪ1900*/
    //printf("%d\n", p->tm_yday); /*ӽ11ΧΪ0-365*/
    stringstream ss;
    ss << filepath << "/" << 1900 + p->tm_year << "-" << \
        1 + p->tm_mon << "-" << \
        p->tm_mday << "-" << \
        8 + p->tm_hour << "-" << \
        p->tm_min << "-" << p->tm_sec;
    ss << ".log";

    m_fout.open(ss.str(), ios::out);
}

LLLoggerFile::~LLLoggerFile() { m_fout.close(); }
int LLLoggerFile::Log(LLCStr module, LL_LogPriority level, LLCStr msg)
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

LLLoggerMix::LLLoggerMix(LL_LogPriority level, LLCStr filename) : LLBaseLogger(level),
                                                                    m_console_log(new LLLoggerConsole(level)),
                                                                    m_file_log(new LLLoggerFile(level, filename))
{

}

LLLoggerMix::~LLLoggerMix()
{
    
}

int LLLoggerMix::Log(LLCStr module, LL_LogPriority level, LLCStr msg)
{
    m_console_log->Log(module, level, msg);
    m_file_log->Log(module, level, msg);
    return 0;
}

LLLoggerNetWork::LLLoggerNetWork(LL_LogPriority level, LLCStr filename) : LLBaseLogger(level)
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

LLLoggerNetWork::~LLLoggerNetWork()
{
    delete m_socket;
}

int LLLoggerNetWork::Log(LLCStr module, LL_LogPriority level, LLCStr msg)
{
    string msg_ = format_msg(module, level, msg);
    m_socket->send(msg_.c_str(), msg_.length());
    return 0;
}
