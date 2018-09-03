#ifndef _PZLOG_H_
#define _PZLOG_H_

#include "Common.h"

#ifdef   __cplusplus
extern "C" {
#endif

    int PZInitLog(PZ_LogMode, PZCStr FileName, PZ_LogPriority level);
    void PZLog(PZCStr mode, PZ_LogPriority level, PZCStr msg);


#ifdef   __cplusplus
}
#endif






#endif // !_PZLOG_H_

