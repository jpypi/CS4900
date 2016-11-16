output.o: output.c | output.h
	$(CC) $(CFLAGS) -c $^ $(LIBS)

.PHONY: test
test:

clean:
	rm -f *.o

.PHONY: test
test: output.o
	@$(CC) -c unittests/unittests.c unittests/cunit.c
	@$(CC) -o unittest output.o unittests.o cunit.o
	@./unittest
