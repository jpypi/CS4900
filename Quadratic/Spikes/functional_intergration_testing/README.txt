This spike intentions are to begin initial steps towards choosing a testing structure.

Some option are to use python scripts or shell scripts to test results of a program's output.


=== FILES IN THIS DIRECTORY ===

    program.c   = source code to our hypothetical main program.
    Makefile    = Makefile for program.c
    outprogram  = The compiled and executable program that will generate some output.
    output.out  = The output that our program (outprogram) generates. The output is stored here.
    
    python_tester.py    = A python script used to do some simple testing to see if output.out meets certain requirements.
    sh_tester.py        = A shell script used to do some simple testing to see if the output.out meets certain requirements.

===============================


+++ TO DO +++

- Discuss with team how we plan on testing programs.
- Choose a language that will be used for functional test scripts.
- Possibly create a testing framework to make tests more consistent and easy to implement.
- Define a testing structure.
- Decide on how we plan on handling tests that failed and how we will log fixes.

+++++++++++++