#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "chat_client.h"

char name[NAME_SIZE];
char message[BUFFER_SIZE];

void Error_Handler(char* msg){
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

void Setting_User_Name(char* user_name){
	sprintf(name, "[%s]", user_name);
}

void* Send_Msg(void* sock){
	int client_sock=*(int*)sock;
	char msg[NAME_SIZE+BUFFER_SIZE+1];

	while(1){
		fgets(message, BUFFER_SIZE, stdin);
		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n")){
			close(client_sock);
			exit(0);
		}
		sprintf(msg, "%s : %s", name, message);
	       	write(client_sock, msg, strlen(msg));	
	}
	return NULL;
}

void* Receive_Msg(void* sock){
	int client_sock=*(int*)sock;
	int msg_len;
	char msg[NAME_SIZE+BUFFER_SIZE];

	while(1){
		msg_len=read(client_sock, msg, NAME_SIZE+BUFFER_SIZE-1);
		if(msg_len==-1)
			return (void*)-1;
		msg[msg_len]=0;
		fputs(msg, stdout);
	}

	return NULL;
}
