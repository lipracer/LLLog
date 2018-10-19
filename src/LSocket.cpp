//
//  LSocket.cpp
//  LLLog
//
//  Created by 陈龙 on 2018/10/19.
//  Copyright © 2018 ___multiMedia___. All rights reserved.
//

#include <stdio.h>
#include <arpa/inet.h>
#include "LSocket.h"

LSocket::LSocket():m_client(int(Socket_Status::Invalid_Sockt)){}

LSocket::LSocket(string ip, int port)
{
    sockaddr_in   servaddr;
    m_client = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if(inet_pton(AF_INET, ip.c_str(), &servaddr.sin_addr) < 0)
    {
        m_client = (int)Socket_Status::Invalid_Sockt;
    }
    if(connect(m_client, (struct sockaddr*)&servaddr, sizeof(servaddr)))
    {
        m_client = (int)Socket_Status::Invalid_Sockt;
    }
    
}

LSocket::~LSocket()
{
    ::close(m_client);
}

int LSocket::send(const char* msg, size_t len)
{
    if(m_client != (int)Socket_Status::Invalid_Sockt)
    {
        return ::send(m_client, msg, len, 0);
    }
    return (int)Socket_Status::Invalid_Sockt;    
}
