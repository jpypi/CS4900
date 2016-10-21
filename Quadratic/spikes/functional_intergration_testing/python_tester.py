#!/usr/bin/python


import sys
import re


def main():

	f = open("output.out", "r")
	test_log = open("testing.log", "w+")

	case1 = f.readline()
	case2 = f.readline()
	case3 = f.readline()

	if (int(case1) == 0):
		test_log.write("Case 1 Passed!\n")
	else:
		test_log.write("Case 1 Failed!!!\n")

	if (int(case2) > 10):
		test_log.write("Case 2 Passed!\n")
	else:
		test_log.write("Case 2 Failed!!!\n")



	return 0;



main()