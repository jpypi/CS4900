# Unit Testing Documentation

## General Guidelines 
- Unit tests shall be clear in explaining its function.
- Unit tests shall follow a consistent naming pattern that is TBD.
- Unit tests will only produce output when they fail. There shall be no output on a successful test.

## F.I.R.S.T. Principles
Unit testing for this project will encourage the implemetation of the F.I.R.S.T. Principles. The acronym is broken down below.
- F – Fast
- I  – Isolated 
- R – Repeatable
- S – Self-Validating
- T – Timely

As folllows, guidelines for the project are set taking the principles in consideration

### Fast

- Description:
	- It is critical for unit tests to be fast. Failing to do so will have a negative impact on the project as it will slow down the development and deployment time. 
- Guidelines:
	- Unit tests should be fast; no single test should take longer than quarter of a second for completion. 


### Isolated
- Description:
	- Test dependency may set off false and result in having the team to figure out which set of tests resulted in the failure.
- Guidelines:
	- Unit tests shall be independent of other test cases. 
	- Unit test shall only test should not reference any external resource other than the specific functionality it is addressing.

### Repeatable
-Description:
	- Consistency is vital in software development. In terms of unit testing, each test should produce the same results each time it is run. 

- Guidelines:
	- If a unit test relies on multi-threading, it must account for race conditions; furthermore shall be thorough to address race conditions.
	- Unit tests shall exhibit consistent behavior and produce the same results across different platforms and operation systems.

### Self-Validating
- Description:
	- All test procedures should the status be determined within its own structure. This means that manual input of test result is unacceptable and should not be used. Manual testing will result in a greater risk and will be more time-consuming.
- Guidelines:
	- Unit tests shall indicate its status as either “pass” or “fail”. Other status codes should be avoided.

### Timely
- Description:
	- The timeliness of when unit tests are written is a very important aspect that will be enforced within the scope of this project.
- Guidelines:
	- Unit tests shall be written within a reasonable time after the corresponding function that needs to be tested is created.

## Authors
Aleks Dobrev
