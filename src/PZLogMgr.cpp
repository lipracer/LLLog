#include "../include/PZLogMgr.h"

PZLogMgr::PZLogMgr() : m_isInit(false),m_log_mode(PZ_LogMode::Log_Default){}
PZLogMgr::~PZLogMgr() 
{
    delete m_logger;
}

int PZLogMgr::InitLogMgr(PZ_LogMode mode, PZCStr filename, PZ_LogPriority level)
{

    if (!m_isInit)
    {
        lock_guard<mutex> _(m_init_mutex);
        if (!m_isInit)
        {            
            m_log_mode = mode;
            m_filename = filename;
            m_log_level = level;
            m_isInit = true;
            m_logger = new PZLogger(level);
        }
    }
    return 0;
}

PZBaseLogger& PZLogMgr::GetLogger()
{
    return *m_logger;
}