#include "../include/LLLogMgr.h"


LLLogMgr::LLLogMgr() : m_isInit(false),m_log_mode(LL_LogMode::Log_Default){}
LLLogMgr::~LLLogMgr() 
{
    delete m_logger;
}

int LLLogMgr::InitLogMgr(LL_LogMode mode, LLCStr filepath, LL_LogPriority level)
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
                    m_logger = new LLLoggerConsole(level);
                    break;
                case Log_File:
                    m_logger = new LLLoggerFile(level, filepath);
                    break;
                case Log_Mix:
                    m_logger = new LLLoggerMix(level, filepath);
                    break;
                case Log_NetWork:
                    m_logger = new LLLoggerNetWork(level, filepath);
                    break;
                default:
                    m_logger = new LLLoggerConsole(level);
                    break;
            }
            
        }
    }
    return 0;
}

LLBaseLogger& LLLogMgr::GetLogger()
{
    return *m_logger;
}
