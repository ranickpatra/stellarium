#include "client.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

Client::Client() {
    //create();
}

Client::~Client() {
    soc_close();
}

// Create a Socket for server communication
short Client::SocketCreate(void)
{

	short hSocket;
	printf("Create the socket\n");
	hSocket = socket(AF_INET, SOCK_STREAM, 0);
	return hSocket;
}

// try to connect with server
int Client::SocketConnect(int hSocket)
{

	int iRetval = -1;
	int ServerPort = 3000;
	struct sockaddr_in remote = {0};

	remote.sin_addr.s_addr = inet_addr("127.0.0.1"); // Local Host
	remote.sin_family = AF_INET;
	remote.sin_port = htons(ServerPort);

	iRetval = connect(hSocket, (struct sockaddr*)&remote, sizeof(struct sockaddr_in));

	return iRetval;
}

// Send the data to the server and set the timeout of 20 seconds
int Client::SocketSend(int hSocket, char* Rqst, short lenRqst)

{

	int shortRetval = -1;
	struct timeval tv;
	tv.tv_sec = 20; /* 20 Secs Timeout */
	tv.tv_usec = 0;

	if (setsockopt(hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof(tv)) < 0)
	{
		printf("Time Out\n");
		return -1;
	}
	shortRetval = send(hSocket, Rqst, lenRqst, 0);

	return shortRetval;
}

// receive the data from the server
int Client::SocketReceive(int hSocket, char* Rsp, short RvcSize)
{

	int shortRetval = -1;
	struct timeval tv;
	tv.tv_sec = 20; /* 20 Secs Timeout */
	tv.tv_usec = 0;

	if (setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv)) < 0)
	{
		printf("Time Out\n");
		return -1;
	}
	shortRetval = recv(hSocket, Rsp, RvcSize, 0);

	printf("Response %s\n", Rsp);

	return shortRetval;
}


int Client::create(void) {
    

	// Create socket
	hSocket = SocketCreate();
	if (hSocket == -1)
	{
		printf("Could not create socket\n");
		return 1;
	}

	printf("Socket is created\n");
    return 0;
}

int Client::soc_close(void) {
    close(hSocket);
	shutdown(hSocket, 0);
	shutdown(hSocket, 1);
	shutdown(hSocket, 2);
    return 0;
}

int Client::sendData(char* data)
{
    create();   // create a socket

	// Connect to remote server
	if (SocketConnect(hSocket) < 0)
	{
		perror("connect failed.\n");
		return 1;
	}

	printf("conected with server\n");

	// Send data to the server
	SocketSend(hSocket, data, strlen(data));

	// Received the data from the server
	// read_size = SocketReceive(hSocket, server_reply, 200);
	// printf("Server Response : %s\n\n", server_reply);

    soc_close();        // close connecgtion
	
	return 0;
}

