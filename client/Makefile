CC = gcc
CFLAGS = -g Wall
TARGET = chat_client
OBJS = chat_client.o chat_client_main.o

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)
chat_client.o : chat_client.c
	$(CC) -c  chat_client.o chat_client.c
chat_client_main.o : chat_client_main.c
	$(CC) -c chat_client_main.o chat_client_main.c

clean : 
	rm $(OBJS) $(TARGET)
