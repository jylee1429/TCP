CC = gcc
CFLAGS = -g -Wall
TARGET = chat_server
OBJS = chat_server.o chat_server_main.o

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)
chat_server.o : chat_server.c
	$(CC) -c chat_server.o chat_server.c
chat_server_main.o : chat_server_main.c
	$(CC) -c chat_server_main.o chat_server_main.c

clean :
	rm $(OBJS) $(TARGET)	
