qsolve.o: qsolve.c | qsolve.h
	$(CC) -c $^ $(CFLAGS) $(LIBS)

## Link the tests
#t1: t1.o
#	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)
#t2: t2.o
#	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)
#
## Compile the tests
#t1.o: t1.c
#	$(CC) $(CFLAGS) -c $^ $(LIBS)
#t2.o: t2.c
#	$(CC) $(CFLAGS) -c $^ $(LIBS)

.PHONY: clean
clean:
	rm -f *.o
