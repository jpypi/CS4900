# Automation Standard
This document describes how automation will be implemented and used in this project.

## Automation system
This project uses make for automation.

## Automation notes
- All src directories must have a Makefile.
- All Makefiles must be able to compile, clean, and run unit tests on their 
    directories with a single command.
- All Makefiles should compile using the "-Wall -pedantic -std=c99" flags.
- Every Makefile in a superdirectory should be able to recursively compile, 
    clean, and run unit tests in subdirectories.
- All Makefiles must have compilation as the first rule.
- All Makefiles must use the rule 'clean' to clean the directory.
- All Makefiles must use the rule 'test' to run all unit tests for the directory.

## Authors
Andrew Gifford
