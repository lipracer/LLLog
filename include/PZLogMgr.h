#ifndef _PZLOGMGR_H_
#define _PZLOGMGR_H_
#include <mutex>
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include "common.h"
#include "PZLogger.h"

using namespace std;
class PZLogMgr 
{

public:
    static PZLogMgr& getInstance() 
    {
        static PZLogMgr log_mgr;
        return log_mgr;        
    }
    int InitLogMgr(PZ_LogMode mode, PZCStr filename, PZ_LogPriority level);
    PZBaseLogger& GetLogger();

private:
    PZLogMgr();
    ~PZLogMgr();

    bool m_isInit;
    mutex m_init_mutex;

    PZ_LogMode m_log_mode;
    string m_filename;
    PZ_LogPriority m_log_level;
    PZBaseLogger* m_logger;



};
#endif // !_PZLOGMGR_H_
