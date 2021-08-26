CC=gcc
CFLAGS=-I.

jepjep: jepjep.c funcs.c
	        $(CC) -Wall -o jepjep jepjep.c funcs.c  -ljson-c -lcurl -I.

clean:
	rm -f jepjep



