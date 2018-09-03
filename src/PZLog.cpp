#include <string>
#include <iostream>
#include "../include/PZLog.h"
#include "../include/PZLogMgr.h"

using namespace std;

int PZInitLog(PZ_LogMode mode, PZCStr filename, PZ_LogPriority level) 
{
    return PZLogMgr::getInstance().InitLogMgr(mode, filename, level);
}

void PZLog(PZCStr mode, PZ_LogPriority level, PZCStr msg)
{
    PZLogMgr::getInstance().GetLogger().Log("test", level, "12344566");
}