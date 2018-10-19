#include <string>
#include <iostream>
#include "../include/PZLog.h"
#include "../include/PZLogMgr.h"

using namespace std;


    
int PZInitLog(PZ_LogMode mode, PZCStr filepath, PZ_LogPriority level)
{
    return PZLogMgr::getInstance().InitLogMgr((PZ_LogMode)mode, filepath, (PZ_LogPriority)level);
}

void PZLog(PZCStr module, PZ_LogPriority level, PZCStr msg)
{
    PZLogMgr::getInstance().GetLogger().Log(module, (PZ_LogPriority)level, msg);
}



