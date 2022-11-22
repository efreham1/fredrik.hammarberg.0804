package org.ioopm.calculator.ast;

/**
* Indicates division by zero was attempted
*/
public class DivisionByZeroException extends Exception {
    public DivisionByZeroException() {
        super();
    }

    /**
    * @param msg A message explaining the reason for the exception being thrown
    */
    public DivisionByZeroException(String msg) {
        super(msg);
    }
}