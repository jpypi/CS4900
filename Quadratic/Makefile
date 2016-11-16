
.PHONY: complile
compile:
	$(MAKE) -C src

.PHONY: clean
clean: 
	$(MAKE) -C src clean

.PHONY: functional_test
functional_test: compile
	@cp src/qsolver test/functional_tests/qsolver
	./test/functional_tests/functional_test_suite.sh
	less test/functional_tests/log.txt
