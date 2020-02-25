//
// Created by 10758 on 2020/2/24.
//

#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <cstring>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

const char *KEY = "U201814853";
const int KEYLEN = sizeof(KEY);

class Packet{
public:
    char *data, *sdata;
    int len;

    Packet(const char* d){
        len = strlen(d) + 1;
        data = new char[len + 4];
        data[3] = (len & 0xff000000) >> 24;
        data[2] = (len & 0x00ff0000) >> 16;
        data[1] = (len & 0x0000ff00) >> 8;
        data[0] = (len & 0x000000ff) >> 0;
        memcpy(data + 4, d, len * sizeof(char));
        sdata = data + 4;
    }

    ~Packet(){
        delete []data;
    }
};

class TCPserver{
public:
    SOCKET servSock, clntSock;
    bool connected;
    SOCKADDR clntAddr;

    TCPserver(){
        //创建套接字
        servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        connected = 0;
    }

    ~TCPserver(){
        Close();
    }

    void Close(){
        closesocket(clntSock);
        if(connected) closesocket(servSock);
    }

    void Listen(const char* IP, int port){
        sockaddr_in sockAddr;
        memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
        sockAddr.sin_family = PF_INET;  //使用IPv4地址
        sockAddr.sin_addr.s_addr = inet_addr(IP);  //具体的IP地址
        sockAddr.sin_port = htons(port);  //端口

        //绑定套接字
        bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        //进入监听状态
        listen(servSock, 20);

        //接收客户端请求
        int nSize = sizeof(SOCKADDR);
        clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

        connected = 1;
    }

    void Send(Packet p){
        int len = p.len + 4;
        char s[len];
        memcpy(s, p.data, len * sizeof(char));

        for(int i = 4; i < len; i++){ //异或加密数据
            s[i] ^= KEY[i % KEYLEN];
        }

        send(clntSock, s, len, 0);
    }
};
 
int main(){
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup( MAKEWORD(2, 2), &wsaData);

    TCPserver S;
    S.Listen("127.0.0.1", 7001);
    S.Send(Packet("Hello World!"));
    S.Send(Packet("This is the second packet."));
    S.Send(Packet("and the third one."));
    S.Close();

    WSACleanup();
    return 0;
}