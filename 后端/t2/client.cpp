//
// Created by 10758 on 2020/2/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

const char *KEY = "U201814853";
const int KEYLEN = sizeof(KEY);

class Packet{
public:
    char *data, *sdata;
    int len;

    Packet(const char* d){
        len = strlen(d) + 1;
        data = new char[len + 4]; //前4个字节存一个int 表示字符串的长度 后面的字节存字符串
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

class TCPclient{
public:
    SOCKET sock;
    char buf[MAXBYTE * 3];
    int buf_len, bufp;
    TCPclient(){
        //创建TCP套接字
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        buf_len = bufp = 0;
    }

    ~TCPclient(){
        closesocket(sock);
    }

    void Connect(const char* IP, int port){
        sockaddr_in sockAddr;

        memset(&sockAddr, 0, sizeof(sockAddr));
        sockAddr.sin_family = PF_INET;
        sockAddr.sin_addr.s_addr = inet_addr(IP);
        sockAddr.sin_port = htons(port);
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    }

    Packet* Receive(){
        while(buf_len - bufp < 4){
            buf_len += recv(sock, buf + buf_len, MAXBYTE, 0);
        }

        int len = *(int*) (buf + bufp); //接受包的长度

        char s[len];

        bufp += 4;
        int sp = 0; //接受字符串
        while(sp < len){
            while(bufp < buf_len && sp < len){
                s[sp++] = buf[bufp++];
            }
            if(bufp == buf_len){
                buf_len = recv(sock, buf, MAXBYTE, 0);
                bufp = 0;
            }
        }

        for(int i = 0; i < len; i++){ //异或解密
            s[i] ^= KEY[i % KEYLEN];
        }


        return new Packet(s);
    }

};

int main(){
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    TCPclient C;
    C.Connect("127.0.0.1", 7001);
    Packet p = *C.Receive();
    printf("1.%s\n", p.sdata);

    p = *C.Receive();
    printf("2.%s\n", p.sdata);

    p = *C.Receive();
    printf("3.%s\n", p.sdata);

    WSACleanup();
    return 0;
}