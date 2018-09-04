#include <string>
#include <iostream>
#include "../include/PZLog.hpp"
#include "../include/PZLogMgr.hpp"

using namespace std;

int PZInitLog(int mode, const char *filepath, int level)
{
    return PZLogMgr::getInstance().InitLogMgr((PZ_LogMode)mode, filepath, (PZ_LogPriority)level);
}

void PZLog(const char * module, int level, const char *msg)
{
    PZLogMgr::getInstance().GetLogger().Log("test", (PZ_LogPriority)level, "12344566");
}