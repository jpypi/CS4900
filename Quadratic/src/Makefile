CC=gcc
CFLAGS=-Wall -pedantic -std=C99
LIBS=-lm

SUBDIRS=qs qsolve input output

all: ${SUBDIRS}

qs:
	$(MAKE) -C $@

qsolve:
	$(MAKE) -C $@

input:
	$(MAKE) -C $@

.PHONY: output
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
	#rm qsolve
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

