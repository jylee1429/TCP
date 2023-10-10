#ifndef _CHAT_CLIENT_H_
#define _CHAT_CLIENT_H_

#define NAME_SIZE 20
#define BUFFER_SIZE 512

void Error_Handler(char* msg);
void Setting_User_Name(char* user_name);
void* Send_Msg(void* sock);
void* Receive_Msg(void* sock);


#endif
