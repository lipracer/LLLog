#ifndef _PZLOG_H_
#define _PZLOG_H_

#include "Common.h"

#ifdef   __cplusplus

extern "C" {

    void PZInitLog(PZ_LogMode, PZCStr FileName, PZ_LogPriority level);

    void PZLog(PZCStr mode, PZCStr msg);

}

#endif






#endif // !_PZLOG_H_

