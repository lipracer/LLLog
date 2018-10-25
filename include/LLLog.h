#ifndef _LLLOG_H_
#define _LLLOG_H_

#include "common.h"

#ifdef   __cplusplus
extern "C" {
#endif

    int LLInitLog(LL_LogMode mode, LLCStr filepath, LL_LogPriority level);
    void LLLog(LLCStr module, LL_LogPriority level, LLCStr msg);


#ifdef   __cplusplus
}
#endif

#endif // !_LLLOG_H_

