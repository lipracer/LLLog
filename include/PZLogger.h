#ifndef _PZLOGGER_H_
#define _PZLOGGER_H_
#include "common.h"
#include <fstream>
#include <thread>

using namespace std;
class PZBaseLogger 
{
public:
    PZBaseLogger(PZ_LogPriority level);
    virtual ~PZBaseLogger();
    virtual int Log(PZCStr module, PZ_LogPriority level, PZCStr msg);

    time_t GetTimePoint();

    thread::id GetThreadId();

    PZ_LogPriority m_level;
};

class PZLoggerConsole : public PZBaseLogger
{
public:
    PZLoggerConsole(PZ_LogPriority level);
    virtual ~PZLoggerConsole();
    virtual int Log(PZCStr module, PZ_LogPriority level, PZCStr msg);
};

class PZLoggerFile : public PZBaseLogger
{
public:
    PZLoggerFile(PZ_LogPriority level, PZCStr filename);
    virtual ~PZLoggerFile();
    virtual int Log(PZCStr module, PZ_LogPriority level, PZCStr msg);

private:
    fstream m_fout;
};

#endif
