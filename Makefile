CC      = /usr/bin/gcc
CFLAGS  = -Wall
LDFLAGS = -lm

OUT = ms5803-14ba

ms5803-14ba: ms5803-14ba.c
	        $(CC) $(CFLAGS) -o $(OUT) ms5803-14ba.c $(LDFLAGS)

clean:
	rm -rf $(OUT)
