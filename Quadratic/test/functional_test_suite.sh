#!/bin/sh -

VALID_TEST_DECRIPTION="
Quadratic formula takes form of    ax^2 + bx + c

A valid test cases assumes the following:

- The input is indeed a quadratic function. Which means:
	+ a does not equal 0.
	+ a,b,c are all real numbers.

- When a,b,c are provided on input they will only be numberical values. Meaning that the input should consist of only characters from the following set {0,1,2,3,4,5,6,7,8,9,0,-,+,.}.

- Valid test cases don't necessaraly have to have solution. If there is no solution for a given test cases, it is still considered a valid test case.

"

ALL_VALID_STRING="This test set contains only valid test cases."
ALL_INVALID_STRING="This test set contains only invalid test cases."
PARTIAL_VALID_STRING="This test set contains both valid and invalid test cases."

NUM_OF_TEST_SETS=3

TEST_SET_0="1 2 3 4 5 6 7"
TEST_SET_0_DESCRIPTION="Let input values a,b,c all be positive integers. Also tests having 0 as input value for b and/or c."
TEST_SET_0_VALIDITY=${ALL_VALID_STRING}

TEST_SET_1="10 11 12"
TEST_SET_1_DESCRIPTION="Let input value a be a positive integer, but let b and c be negative integers."
TEST_SET_1_VALIDITY=${ALL_VALID_STRING}

TEST_SET_2="20 21 22 23 24 25"
TEST_SET_2_DESCRIPTION="Let input values a and b be positive integers, but let c be a negative integer."
TEST_SET_2_VALIDITY=${ALL_VALID_STRING}

#### Test sets below don't currently exist. Just here as stubs for now.###

TEST_SET_3="30"
TEST_SET_3_DESCRIPTION="Let input values a,b,c all be negative integers."
TEST_SET_3_VALIDITY=${ALL_VALID_STRING}

TEST_SET_4="40"
TEST_SET_4_DESCRIPTION="Let input value a be a negative interger, but let b and c be positive integers."
TEST_SET_4_VALIDITY=${ALL_VALID_STRING}

TEST_SET_5="50"
TEST_SET_5_DESCRIPTION="Let input values a and c be negative integers, but let b be a positive integer."
TEST_SET_5_VALIDITY=${ALL_VALID_STRING}

TEST_SET_6="60"
TEST_SET_6_DESCRIPTION=" "

##############################################################################
##############################################################################

createNewLog()
{
	timestamp=$(date +%Y-%m-%d)
	initial_message="Log generated on ${timestamp}. \n"

	echo "${initial_message}" > log.txt
}

##############################################################################

executeTestSet()
{
	THIS_TEST_SET=$1
	THIS_TEST_SET_DESCRIPTION=$2
	THIS_TEST_SET_VALIDITY=$3
	THIS_TEST_SET_NUMBER=$4

	SEPARATOR="==================================================\n"
	SEPARATOR2="--------------------------------------------------\n"
	
	echo "\n\n${SEPARATOR}${SEPARATOR}" >> log.txt
	echo "\nEXECUTING TEST SET #${THIS_TEST_SET_NUMBER}\n" >> log.txt
	echo "\nDescription for this test set:\n${THIS_TEST_SET_DESCRIPTION}\n" >> log.txt
	echo "${THIS_TEST_SET_VALIDITY}\n" >> log.txt
	echo "${SEPARATOR2}\n\n" >> log.txt

	for TEST in ${THIS_TEST_SET}
	do
		echo "||| TEST CASE ${TEST} |||\n\n" >> log.txt
		./qsolver < input_${TEST}.txt > output_${TEST}.txt
		diff output_${TEST}.txt expected_output_${TEST}.txt > /dev/null
		
		if [ "${?}" = "0" ]
		then
			echo "TEST SUCCESSFULL!\n" >> log.txt
		else
			echo "TEST FAILED!\nMore information shown below.\n\n" >> log.txt
			
			#diff_result=$( { diff "output_${TEST}.txt" "expected_output_${TEST}.txt"; } 2>&1 )
			echo "Input:\n" >> log.txt
			cat input_${TEST}.txt >> log.txt
			echo "\nExpected output:\n" >> log.txt
			cat expected_output_${TEST}.txt >> log.txt
			echo "\nGenerated output:\n" >> log.txt
			cat output_${TEST}.txt >> log.txt

			#echo "${diff_result}" >> log.txt
			echo "\n\n" >> log.txt
		fi
		
		echo "${SEPARATOR2}" >> log.txt
	
	done

}


##############################################################################
##############################################################################

######### MAIN ##########

#Create a new log (delete old one if it exists).
createNewLog

#Initiate counter to step through test sets.
i=0

#Iterate and execute all test sets.
while [ $i -lt $NUM_OF_TEST_SETS ]
do
	i_string="${i}"
	eval CURRENT_TEST_SET='$'"TEST_SET_${i_string}"
	eval CURRENT_TEST_SET_DESCRIPTION='$'"TEST_SET_${i_string}_DESCRIPTION"
	eval CURRENT_TEST_SET_VALIDITY='$'"TEST_SET_${i_string}_VALIDITY"

	executeTestSet "${CURRENT_TEST_SET}" "${CURRENT_TEST_SET_DESCRIPTION}" "${CURRENT_TEST_SET_VALIDITY}" "${i_string}"

	i=$((i+1))
done










