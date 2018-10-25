#include <string>
#include <iostream>
#include "../include/LLLog.h"
#include "../include/LLLogMgr.h"

using namespace std;


    
int LLInitLog(LL_LogMode mode, LLCStr filepath, LL_LogPriority level)
{
    return LLLogMgr::getInstance().InitLogMgr((LL_LogMode)mode, filepath, (LL_LogPriority)level);
}

void LLLog(LLCStr module, LL_LogPriority level, LLCStr msg)
{
    LLLogMgr::getInstance().GetLogger().Log(module, (LL_LogPriority)level, msg);
}



