#include "chat_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <unistd.h>

int client_socks[MAX_CLIENT];
int client_cnt;
pthread_mutex_t mutx;

void Error_Handler(char* message){
	fputs(message, stderr);
	fputc('\t', stderr);
	exit(1);
}

// send to all
void Send_Message(char* msg, int len){
	int i;
	pthread_mutex_lock(&mutx);
	for(i=0;i<client_cnt;i++){
		write(client_socks[i], msg, len);
	}
	pthread_mutex_unlock(&mutx);
}

void *Client_Handler(void* sock){
	int client_sock	= *(int *)sock;
	int str_len, i;
	char msg[BUFFER_SIZE];
	// read and send
	while((str_len=read(client_sock, msg, sizeof(msg)))!=0){
		fputc(str_len, stdout);
		Send_Message(msg, str_len);	
	}

	pthread_mutex_lock(&mutx);
	for(i=0;i<client_cnt;i++){
		if(client_sock==client_socks[i]){
			printf("i = %d\n", i);
			//while(i++<client_cnt-1){
			//	client_socks[i]=client_socks[i+1];
			//}
			//break;
			while(i<client_cnt-1){
		 		client_socks[i]=client_socks[i+1];
				i++;
			}
			break;
		}
	}
	client_cnt--;
	pthread_mutex_unlock(&mutx);
	close(client_sock);
	return NULL;
}
