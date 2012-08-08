CC      = /usr/bin/gcc
CFLAGS  = -Wall
LDFLAGS = -lm

ms5803_out = ms5803-14ba.o
main_out = main

main: ms5803-14ba main.c
	$(CC) $(CFLAGS) -o $(main_out) main.c $(ms5803_out) $(LDFLAGS)

ms5803-14ba: ms5803-14ba.c
	$(CC) $(CFLAGS) -o $(ms5803_out) -c ms5803-14ba.c $(LDFLAGS)

clean:
	rm -rf $(ms5803_out) $(main_out) 
