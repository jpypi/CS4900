CC=gcc
CFLAGS=-Wall -pedantic -std=c99
LIBS=-lm

SUBDIRS=qs qsolve input output sqrt validate
INCLUDE_DIRS=$(addprefix -I../,$(SUBDIRS))
CFLAGS += $(INCLUDE_DIRS)

TESTSUBDIRS=$(addsuffix test,$(SUBDIRS))

export CC CFLAGS LIBS INCLUDE_DIRS

.PHONY: $(SUBDIRS)
qsolver: $(SUBDIRS)
	$(CC) -o $@ $(addsuffix /*.o,$(SUBDIRS)) $(CFLAGS) $(LIBS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: test
test: $(TESTSUBDIRS)

$(TESTSUBDIRS):
	$(MAKE) -C $(subst test,,$@) test


.PHONY: clean
clean:
	rm -f *.o
	rm -f qsolver
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

