#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>


#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)

int main() {

	SOCKET client_socket;
	WSADATA wsaStructure;
	int initStatus;
	struct sockaddr_in client_addr;
	char sendData[500] = "Hello this is winClient";
	char recvData[500];


	/* Initialize Socket */
	initStatus = WSAStartup(MAKEWORD(2,2), &wsaStructure); 

	if (!initStatus != 0) {
		printf("WINSOCK ERROR - Unable to Initialize Socket");
		return 1;
	}
	

	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(9001);
	client_addr.sin_addr.s_addr = inet_addr("192.168.66.130");


	connect(client_socket, (SOCKADDR*) &client_addr, sizeof(client_addr));
	recv(client_socket, recvData, sizeof(recvData), 0);
	printf("Data from server: %s", recvData);
	send(client_socket, sendData, sizeof(sendData), 0);
	closesocket(client_socket);
	WSACleanup();
	return 0;
}