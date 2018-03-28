C=gcc
CFLAGS=-g -Wall -O0 -lpthread -pthread -std=c99

all:
        $(CC) $(CFLAGS) -o netbenchtcp MynetbenchTCP.c
	$(CC) $(CFLAGS) -o netbenchudp MynetbenchUDP.c

clean:
        $(RM) *.o netbenchtcp
	$(RM) *.o netbenchudp

