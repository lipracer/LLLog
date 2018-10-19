//
//  LSocket.h
//  LLLog
//
//  Created by 陈龙 on 2018/10/19.
//  Copyright © 2018 ___multiMedia___. All rights reserved.
//

#ifndef _LSocket_h
#define _LSocket_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>

#include <string>

using namespace std;

enum class Socket_Status : int
{
   Invalid_Sockt = -1,
};

class LSocket
{
public:
    LSocket();
    LSocket(string ip, int port);
    ~LSocket();
    int send(const char* msg, size_t len);
private:
public:
private:
    int m_client;
    
};

#endif /* LSocket_h */
