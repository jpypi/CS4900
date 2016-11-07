CC=gcc
CFLAGS=-Wall -pedantic -std=c99
LIBS=-lm

SUBDIRS=qs qsolve input output
INCLUDE_DIRS=-I../qs -I../qsolve -I../input -I../output

export CC CFLAGS LIBS INCLUDE_DIRS

.PHONY: all qs qsolve input output
qsolver: ${SUBDIRS}
	$(CC) -o $@ qs/*.o qsolve/*.o input/*.o output/*.o $(CFLAGS) $(LIBS)

qs:
	$(MAKE) -C $@
qsolve:
	$(MAKE) -C $@
input:
	$(MAKE) -C $@
output:
	$(MAKE) -C $@

.PHONY: test
test:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir test; \
	done

.PHONY: clean
clean:
	rm -f *.o
	rm -f qsolver
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

