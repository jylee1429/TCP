#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "chat_server.h"

extern int client_socks[MAX_CLIENT];
extern int client_cnt;
extern pthread_mutex_t mutx;

int main(int argc, char* argv[]){
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_size;
	pthread_t server_tid;
	
	if(argc!=2){
		printf("Useage : %s <PORT>\n", argv[0]);
		exit(1);
	}

	client_cnt=0;

	server_sock=socket(AF_INET, SOCK_STREAM, 0);
	if(server_sock==-1)
		Error_Handler("socket error");
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[1]));
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr))==-1)
		Error_Handler("bind error");

	if(listen(server_sock, 5)==-1)
		Error_Handler("listen error");

	pthread_mutex_init(&mutx, NULL);
	
	while(1){
		client_addr_size=sizeof(client_addr);
		client_sock=accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
		if(client_sock==-1)
			Error_Handler("accept error");
		
		pthread_mutex_lock(&mutx);
		client_socks[client_cnt++]=client_sock;
		pthread_mutex_unlock(&mutx);

		pthread_create(&server_tid, NULL, Client_Handler, (void*)&client_sock);
		pthread_detach(server_tid);
		printf("Connected client IP : %s\n", inet_ntoa(client_addr.sin_addr));
	}

	close(server_sock);

	return 0;
}


