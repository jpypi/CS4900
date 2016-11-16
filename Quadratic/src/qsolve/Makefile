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

.PHONY: test
test: qsolve.o ../validate/validate.o ../sqrt/sqrt.o
	@$(CC) -c unittests/unittests.c unittests/cunit.c unittests/mockunittests.c unittests/mock_qsolve_sqrt.c
	@$(CC) -o unittest qsolve.o unittests.o cunit.o ../validate/validate.o ../sqrt/sqrt.o $(LIBS) -lm
	@./unittest
	@$(CC) -o mockunittest qsolve.o mockunittests.o cunit.o ../validate/validate.o mock_qsolve_sqrt.o $(LIBS) -lm
	@./mockunittest
