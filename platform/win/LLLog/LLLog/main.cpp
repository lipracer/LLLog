#include <iostream>
#include "../../../../include/PZLog.h"

int main() 
{
    PZInitLog((PZ_LogMode)1, "", (PZ_LogPriority)1);
    PZLog("456", "123");
    system("pause");
}