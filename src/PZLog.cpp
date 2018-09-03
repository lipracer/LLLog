#include <string>
#include <iostream>
#include "../include/PZLog.h"
#include "../include/PZLogMgr.h"

using namespace std;

void PZInitLog(PZ_LogMode mode, PZCStr filename, PZ_LogPriority level) 
{
    PZLogMgr::getInstance().InitLogMgr(mode, filename, level);
}

void PZLog(PZCStr mode, PZCStr msg)
{
    PZLogMgr::getInstance().GetLogger().Log("test", PZ_LogPriority::LOG_DEBUG, "12344566");
}