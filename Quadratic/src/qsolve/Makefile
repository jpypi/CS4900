qsolve.o: qsolve.c | qsolve.h
	$(CC) -c $^ $(CFLAGS) $(LIBS)


.PHONY: test1 test2
test1: test1.o qsolve.o mock_sqrt.o
	$(CC) $^ $(CFLAGS)

test2: test2.o qsolve.o
	$(CC) $^ $(CFLAGS) $(LIBS)

test1.o: test1.c | qsolve.h
	$(CC) -c $^ $(CFLAGS) $(LIBS)
test2.o: test2.c | qsolve.h
	$(CC) -c $^ $(CFLAGS) $(LIBS)


.PHONY: clean
clean:
	rm -f *.o
