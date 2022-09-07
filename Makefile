CC=gcc

%.o: %.c
	$(CC) -c -o $@ $<

ll : ll.o
     gcc .o unix unix.o
	
clean:
	rm -f *.o unix.o