package org.ioopm.calculator.ast;

/**
* Indicates an illegal expression was encountered during evaluation
*/
public class IllegalExpressionException extends Exception {
    public IllegalExpressionException() {
        super();
    }

    /**
    * @param msg A message explaining the reason for the exception being thrown
    */
    public IllegalExpressionException(String msg) {
        super(msg);
    }
}