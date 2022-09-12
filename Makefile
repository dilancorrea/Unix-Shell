CC=gcc

%.o: %.c
	$(CC) -c -o $@ $<

unix: unix.o
	gcc -o unix unix.o


tar:
	tar czvf c_language_basics.tgz *.c 
	
clean:
	rm -f *.o unix