#ifndef _LLLOGGER_H_
#define _LLLOGGER_H_
#include "common.h"
#include <fstream>
#include <thread>

#include "LSocket.h"

using namespace std;
class LLBaseLogger 
{
public:
    LLBaseLogger(LL_LogPriority level);
    virtual ~LLBaseLogger();
    virtual int Log(LLCStr module, LL_LogPriority level, LLCStr msg);

    LL_LogPriority m_level;
};

class LLLoggerConsole : public LLBaseLogger
{
public:
    LLLoggerConsole(LL_LogPriority level);
    virtual ~LLLoggerConsole();
    virtual int Log(LLCStr module, LL_LogPriority level, LLCStr msg);
};

class LLLoggerFile : public LLBaseLogger
{
public:
    LLLoggerFile(LL_LogPriority level, LLCStr filename);
    virtual ~LLLoggerFile();
    virtual int Log(LLCStr module, LL_LogPriority level, LLCStr msg);

private:
    fstream m_fout;
    mutex m_mtx;
};

class LLLoggerMix : public LLBaseLogger
{
public:
    LLLoggerMix(LL_LogPriority level, LLCStr filename);
    virtual ~LLLoggerMix();
    virtual int Log(LLCStr module, LL_LogPriority level, LLCStr msg);
private:
    //避免多重继承
    LLBaseLogger* m_console_log;
    LLBaseLogger* m_file_log;
};

class LLLoggerNetWork : public LLBaseLogger
{
public:
    LLLoggerNetWork(LL_LogPriority level, LLCStr filename);
    virtual ~LLLoggerNetWork();
    virtual int Log(LLCStr module, LL_LogPriority level, LLCStr msg);
private:
public:
private:
    LSocket *m_socket;
};

#endif
