# Assignment 4

Simon Eriksson & Fredrik Hammarberg

sier8161 / frha0804

2022-12-02

---

## Building and running

To build the Interpreter and all it's dependencies, use the command

	`$ make`

Then run the Interpreter with the command

	`$ make run`

### Information about the calculator

Unary operator names and commands are case sensitive and begin with a capital letter.

Syntax errors give the read-out "Expected Number".

If a variable is created with the same name as a function the function get removed
and vice versa.

When in function parsing mode, typing "Quit" aborts the function parsing and
removes the current function.

A class named Function was added to the AST to simplify handling functions.

Syntax of scopes is {expression} where anything entered inside the scope will be
evaluated but variables set inside will not transfer to the global scope.

Functions may not be declared inside a scope and are only allowed to be created
in the root environment.

However variables and functions set _outside_ of a scope are accesible from inside scopes.

---

####  Tests

To run tests of the Interpreter using JUnit and stdin redirection:

	`$ make test`

This will run unit tests and integration tests of the abstract syntax tree and
parser and also system tests of the entire interpreter.
NOTE: to make this work - update the JUNIT_PATH variable in the Makefile to match your local JUnit path

---

#### Documentation

To generate documentation with javadoc, use the command

	`$ make docs`

The documentation files will be stored in the directory `doc`
