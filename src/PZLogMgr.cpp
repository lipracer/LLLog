#include "../include/PZLogMgr.h"


PZLogMgr::PZLogMgr() : m_isInit(false),m_log_mode(PZ_LogMode::Log_Default){}
PZLogMgr::~PZLogMgr() 
{
    delete m_logger;
}

int PZLogMgr::InitLogMgr(PZ_LogMode mode, PZCStr filepath, PZ_LogPriority level)
{

    if (!m_isInit)
    {
        lock_guard<mutex> _(m_init_mutex);
        if (!m_isInit)
        {            
            m_log_mode = mode;
            //m_filename = filepath;
            m_log_level = level;
            m_isInit = true;
            switch(mode)
            {
                case Log_Console:
                    m_logger = new PZLoggerConsole(level);
                    break;
                case Log_File:
                    m_logger = new PZLoggerFile(level, filepath);
                    break;
                case Log_Mix:
                    m_logger = (PZLoggerConsole*)(new PZLoggerMix(level, filepath));
                default:
                    m_logger = new PZLoggerConsole(level);
                    break;
            }
            
        }
    }
    return 0;
}

PZBaseLogger& PZLogMgr::GetLogger()
{
    return *m_logger;
}
