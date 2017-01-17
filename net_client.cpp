#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")
 
using namespace std;

int main(){
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        cout << "원속초기화 실패"<<endl;
        system("pause");
        return 1;
    }		
	char i_url[100];
	string firstorder ="GET / HTTP/1.1\r\nHost:";
	string lastorder ="\r\nConnection: close\r\n\r\n";
	string o_url;

	cout <<"연결할 URL을 입력하세요"<<endl;
	cout <<"URL 입력 : ";
	cin >> i_url;

	firstorder.append(i_url);
	o_url = firstorder.append(lastorder);
	const char *cstr = o_url.c_str();	

    cout << "연결중.."<<endl;

	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct hostent *host;
	host = gethostbyname(i_url);
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port=htons(80);
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
        cout << "연결 할 수 없습니다."<<endl;
        system("pause");
        return 1;
    }

    cout << "연결되었습니다."<<endl;
	send(Socket,cstr,strlen(cstr),0);	

	char buffer[100000] = {0};
    int nDataLength = 0;
   while((nDataLength = recv(Socket,buffer,100000,0)) > 0){
		int i = 0;
		while(buffer[i] !=0) {		
		cout << buffer[i];
			i += 1;
		}
    }
    closesocket(Socket);
    WSACleanup();
    system("pause");
    return 0;
}