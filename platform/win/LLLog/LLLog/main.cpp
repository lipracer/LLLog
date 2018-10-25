#include <iostream>
#include <thread>
#include <sstream>
#include "../../../../include/LLLog.hpp"
#include "../../../../include/LLLog.hpp"

using namespace std;

int main() 
{
    LLInitLog(1, ".", 1);
    for (size_t i = 0; i < 1; i++)
    {
        stringstream ss;
        ss << i;
        thread th(LLLog, "test:", LL_LogPriority::LOG_ERROR, ss.str().c_str());
        th.detach();
        ss.flush();
        ss.str("");
    }
    
    system("pause");
}