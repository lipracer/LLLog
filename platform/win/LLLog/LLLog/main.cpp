#include <iostream>
#include <thread>
#include <sstream>
#include "../../../../include/PZLog.h"
#include "../../../../include/PZLogMgr.h"

using namespace std;

int main() 
{
    PZInitLog((PZ_LogMode)1, "", (PZ_LogPriority)1);
    for (size_t i = 0; i < 100; i++)
    {
        stringstream ss;
        ss << i;
        thread th(PZLog, "test:", PZ_LogPriority::LOG_ERROR, ss.str().c_str());
        th.detach();
        ss.flush();
        ss.str("");
    }
    
    system("pause");
}