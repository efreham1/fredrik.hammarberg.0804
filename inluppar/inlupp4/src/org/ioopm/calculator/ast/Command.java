package org.ioopm.calculator.ast;

/**
* Abstract class for command expression nodes
*/
public abstract class Command extends SymbolicExpression {
    public Command(String name) {
        super(name);
    }

    @Override
    public boolean isCommand() {
        return true;
    }
}