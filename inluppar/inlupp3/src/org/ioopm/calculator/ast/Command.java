package org.ioopm.calculator.ast;

/**
* Abstract class for command expression nodes
*/
public abstract class Command extends SymbolicExpression {
    public Command(String name) {
        super(name);
    }

    public SymbolicExpression eval(Environment vars) {
        throw new RuntimeException("eval() called on Command type.");
    }

    public boolean isCommand() {
        return true;
    }
}