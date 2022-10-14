#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int interactionMenu(const SOCKET);

int main() {


	/* Declare variables */
	int server_socket; 
	int client_socket; 
	int menuOptionToSend = NULL;
	struct sockaddr_in server_addr;
	char send_buffer[500] = "SEVER CONNECTION SUCCESS";
	char recv_buffer[500];

	/* Create TCP Socket */
	server_socket = socket(AF_INET, SOCK_STREAM, 0); 

	/* Populate sockaddr_in Structure*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9001);
	server_addr.sin_addr.s_addr = inet_addr("192.168.66.130");

	bind(server_socket, (struct server_addr*)&server_addr, sizeof(server_addr));
	listen(server_socket, 5);

	client_socket = accept(server_socket, NULL, NULL); //accept the client 
	printf("Client Connected\n");
	send(client_socket, send_buffer, sizeof(send_buffer), 0); // send to client that it succesfully connected
	
	menuOptionToSend = interactionMenu(server_socket); // Get user to selct what it wants the client to do
	send(client_socket, menuOptionToSend, sizeof(menuOptionToSend), 0);

	recv(client_socket, recv_buffer, sizeof(recv_buffer), 0);
	printf("Client has sent: %s", recv_buffer);


	return 0;
}
int interactionMenu(SOCKET server_socket){
	int menuOpt;	
	while(1){
		printf("[1] - Get IP address\n");
		printf("[2] - Send File to client\n");
		printf("[3] - Get running processes from client\n");
		printf("[4] - Exit Program\n");
		menuOpt = scanf("%d", &menuOpt);
	}
	if(menuOpt == 4){
		close(server_socket);
		return 0;
	}
	
	return menuOpt;
}
