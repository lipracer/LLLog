#include "../include/PZLogger.h"
#include <iostream>
using namespace std;

PZCStr LogLevelInfo[] = { "UNKNOWN", "DEFAULT", "VERBOSE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL", "SILENT" };


PZBaseLogger::PZBaseLogger(PZ_LogPriority level):m_level(level) {}
PZBaseLogger::~PZBaseLogger() {}
int PZBaseLogger::Log(PZCStr module, PZ_LogPriority level, PZCStr msg)
{
    cout << "PZBaseLogger:" << msg << endl;
    return 0;
}

PZLogger::PZLogger(PZ_LogPriority level) : PZBaseLogger(level)
{
}

PZLogger::~PZLogger() {}
int PZLogger::Log(PZCStr module, PZ_LogPriority level, PZCStr msg)
{
    if (level > m_level)
    {
        cout << "[PZLogger]" << " " << module << " " << "[" << LogLevelInfo[(int)level] << "]" << msg << endl;
    }
    
    return 0;
}