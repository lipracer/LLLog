#ifndef _PZLOGGER_H_
#define _PZLOGGER_H_
#include "common.h"
#include <fstream>
#include <thread>

#include "LSocket.h"

using namespace std;
class PZBaseLogger 
{
public:
    PZBaseLogger(PZ_LogPriority level);
    virtual ~PZBaseLogger();
    virtual int Log(PZCStr module, PZ_LogPriority level, PZCStr msg);

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
    mutex m_mtx;
};

class PZLoggerMix : public PZBaseLogger
{
public:
    PZLoggerMix(PZ_LogPriority level, PZCStr filename);
    virtual ~PZLoggerMix();
    virtual int Log(PZCStr module, PZ_LogPriority level, PZCStr msg);
private:
    //避免多重继承
    PZBaseLogger* m_console_log;
    PZBaseLogger* m_file_log;
};

class PZLoggerNetWork : public PZBaseLogger
{
public:
    PZLoggerNetWork(PZ_LogPriority level, PZCStr filename);
    virtual ~PZLoggerNetWork();
    virtual int Log(PZCStr module, PZ_LogPriority level, PZCStr msg);
private:
public:
private:
    LSocket *m_socket;
};

#endif
