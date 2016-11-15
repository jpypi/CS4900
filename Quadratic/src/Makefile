CC=gcc
CFLAGS=-Wall -pedantic -std=c99
LIBS=-lm

SUBDIRS=qs qsolve input output sqrt
INCLUDE_DIRS=$(addprefix -I../,$(SUBDIRS))
CFLAGS += $(INCLUDE_DIRS)

export CC CFLAGS LIBS INCLUDE_DIRS

.PHONY: all $(SUBDIRS)
qsolver: $(SUBDIRS)
	$(CC) -o $@ $(addsuffix /*.o,$(SUBDIRS)) $(CFLAGS) $(LIBS)

$(SUBDIRS):
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

