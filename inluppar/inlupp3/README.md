# Assignment 3

Johan Yrefors & Fredrik Hammarberg

joyr0993 / frha0804

2022-11-16

---

## Building and running

To build the Calculator and all it's dependencies, use the command

	`$ make`

Then run the Calculator with the command

	`$ make run`

### Information about the calculator

Unary operator names and commands are case sensitive and begin with a capital letter.
Syntax errors give the read-out "Expected Number".

---

#### Unit tests

To run unit tests of the AST using JUnit:

	`$ make test`

NOTE: to make this work - update the JUNIT_PATH variable in the Makefile to match your local JUnit path

---

#### Documentation

To generate documentation with javadoc, use the command

	`$ make docs`

The documentation files will be stored in the directory `doc`
