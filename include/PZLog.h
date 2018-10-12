#ifndef _PZLOG_H_
#define _PZLOG_H_

#include "common.h"

#ifdef   __cplusplus
extern "C" {
#endif

    int PZInitLog(PZ_LogMode mode, PZCStr filepath, PZ_LogPriority level);
    void PZLog(PZCStr module, PZ_LogPriority level, PZCStr msg);


#ifdef   __cplusplus
}
#endif






#endif // !_PZLOG_H_

