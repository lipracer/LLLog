#ifndef _LLLOGMGR_H_
#define _LLLOGMGR_H_
#include <mutex>
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include "common.h"
#include "LLLogger.h"

using namespace std;
class LLLogMgr 
{

public:
    static LLLogMgr& getInstance() 
    {
        static LLLogMgr log_mgr;
        return log_mgr;        
    }
    int InitLogMgr(LL_LogMode mode, LLCStr filename, LL_LogPriority level);
    LLBaseLogger& GetLogger();

private:
    LLLogMgr();
    ~LLLogMgr();

    bool m_isInit;
    mutex m_init_mutex;

    LL_LogMode m_log_mode;
    string m_filename;
    LL_LogPriority m_log_level;
    LLBaseLogger* m_logger;



};
#endif // !_LLLOGMGR_H_
