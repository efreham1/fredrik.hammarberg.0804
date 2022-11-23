package org.ioopm.calculator.parser;

public class SyntaxErrorException extends Exception {
    public SyntaxErrorException() {
        super();
    }
    public SyntaxErrorException(String msg) {
        super(msg);
    }
}