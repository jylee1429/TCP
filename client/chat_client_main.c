#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "chat_client.h"

int main(int argc, char* argv[]){
	int client_sock;
	struct sockaddr_in server_addr;
	pthread_t send_tid, receive_tid;
	void* thread_return;

	if(argc != 4){
		printf("Use : %s <NAME> <IP> <PORT>\n", argv[0]);
		exit(1);
	}

	Setting_User_Name(argv[1]);

	client_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(argv[2]);
	server_addr.sin_port=htons(atoi(argv[3]));

	if(connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr))==-1)
		Error_Handler("connect error");
	else
		puts("connecting....");

	
	pthread_create(&send_tid, NULL, Send_Msg, (void*)&client_sock);
	pthread_create(&receive_tid, NULL, Receive_Msg, (void*)&client_sock);
	pthread_join(send_tid, &thread_return);
	pthread_join(receive_tid, &thread_return);
	
	close(client_sock);
	return 0;
}


