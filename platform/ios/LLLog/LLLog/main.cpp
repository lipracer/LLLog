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
#include "PZLog.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    PZInitLog(Log_Console, "", LOG_DEBUG);
    
    PZLog("", LOG_ERROR, "");
    
    return 0;
}
