#include <iostream>
#include <thread>
#include <sstream>
#include "../../../../include/PZLog.hpp"
#include "../../../../include/PZLog.hpp"

using namespace std;

int main() 
{
    PZInitLog(1, ".", 1);
    for (size_t i = 0; i < 1; i++)
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