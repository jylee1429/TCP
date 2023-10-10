#ifndef _CHAT_SERVER_H_
#define _CHAT_SERVER_H_

#include <pthread.h>

#define MAX_CLIENT 100
#define BUFFER_SIZE 1024

void Error_Handler(char* message);
void Send_Message(char* msg, int len);
void *Client_Handler(void* sock);


#endif
