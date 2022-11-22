JUNIT_PATH = /home/fredrik/Local_reps/lib/junit-platform-console-standalone-1.9.1.jar
## NOTE: You need to change JUNIT_PATH to your local JUnit path in order to run unit tests
CAL_PATH   = ./src/org/ioopm/calculator
AST_PATH   = $(CAL_PATH)/ast
PAR_PATH   = $(CAL_PATH)/parser

all:
	javac -d classes -sourcepath src src/org/ioopm/calculator/Calculator.java

run:
	java -cp classes org.ioopm.calculator.Calculator

clean:
	rm -rf classes

test:
	javac -d classes -cp $(JUNIT_PATH):classes -sourcepath src AstUnitTests.java
	java -jar $(JUNIT_PATH) -cp classes -c AstUnitTests

docs:
	javadoc -d doc -classpath classes -sourcepath src org.ioopm.calculator -subpackages org.ioopm.calculator

.PHONY: all classes clean ast_test
