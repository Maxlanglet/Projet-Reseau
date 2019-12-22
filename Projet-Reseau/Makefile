CC = gcc
CPPFLAGS=
CFLAGS = -Wall -Werror -Wpedantic -std=c11
LDFLAGS = 

ifeq ($(DEBUG), 1)
	CPPFLAGS += -g
endif

all: Reseau_client Reseau_server clean

Reseau_client: Reseau_client.o
	$(CC) $(LDFLAGS) -o $@ $^

Reseau_client.o: Reseau_client.c

Reseau_server: anagram.o personal_strings.o Reseau_server.o
	$(CC) $(LDFLAGS) -o $@ $^

Reseau_server.o: Reseau_server.c

anagram.o: anagram.c
	$(CC) $(CFLAGS) -c anagram.c

personal_strings.o: personal_strings.c
	$(CC) $(CFLAGS) -c personal_strings.c

clean:
	rm -f *.o
