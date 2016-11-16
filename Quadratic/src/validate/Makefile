validate.o: validate.c | validate.h
	$(CC) $(CFLAGS) -c $^ $(LIBS)

clean:
	rm -f *.o

.PHONY: test
test: validate.o
	@$(CC) -c unittests/unittests.c unittests/cunit.c
	@$(CC) -o unittest validate.o unittests.o cunit.o
	@./unittest
