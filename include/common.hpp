#ifndef _COMMON_H_
#define _COMMON_H_
 
enum class PZ_LogPriority : int
{
    LOG_UNKNOWN = 0,
    LOG_DEFAULT,
    LOG_VERBOSE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
    LOG_SILENT
};
enum class PZ_LogMode : unsigned int 
{
    Log_Default = 0,
    Log_Console = 0x01,
    Log_File = 0x02,
    Log_Mix = 0x03
};

using PZCStr = const char*;

extern PZCStr LogLevelInfo[];


#endif // 
