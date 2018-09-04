#ifndef _PZLOG_H_
#define _PZLOG_H_

#include "common.hpp"

#ifdef   __cplusplus
extern "C" {
#endif

    int PZInitLog(int, const char *filepath, int level);
    void PZLog(const char *module, int level, const char *msg);


#ifdef   __cplusplus
}
#endif






#endif // !_PZLOG_H_

