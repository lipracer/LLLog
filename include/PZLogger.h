#ifndef _PZLOGGER_H_
#define _PZLOGGER_H_
#include "Common.h"

class PZBaseLogger 
{
public:
    PZBaseLogger(PZ_LogPriority level);
    virtual ~PZBaseLogger();
    virtual int Log(PZCStr module, PZ_LogPriority level, PZCStr msg);

    PZ_LogPriority m_level;
};

class PZLogger : public PZBaseLogger
{
public:
    PZLogger(PZ_LogPriority level);
    virtual ~PZLogger();
    virtual int Log(PZCStr module, PZ_LogPriority level, PZCStr msg);
};

#endif