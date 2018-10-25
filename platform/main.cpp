//
//  main.cpp
//  LLLog
//
//  Created by multimedia on 2018/9/14.
//  Copyright © 2018年 ___multiMedia___. All rights reserved.
//

#include <iostream>
#include <string>
#include "common.h"
#include "LLLog.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    LLInitLog(Log_NetWork, "127.0.0.1:9090", LOG_DEBUG);
    
    while(true)
    {
        LLLog("12", LOG_ERROR, "12");
    }
    
    return 0;
}
