
input.o: input.c | input.h
	$(CC) -c $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o

.PHONY: test
test: input.o
	@$(CC) -c unittests/unittests.c unittests/cunit.c
	@$(CC) -o unittest input.o unittests.o cunit.o
	@./unittest <unittests/test.in
