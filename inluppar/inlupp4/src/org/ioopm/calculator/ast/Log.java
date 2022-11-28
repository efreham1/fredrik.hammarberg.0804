package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
/**
* Logarithm node
*/
public class Log extends Unary {
    public Log(SymbolicExpression arg) {
        super("Log", arg);
    }

    /**
    * @return String representation for the operation
    */
    @Override
    public String getName() {
        return "Log";
    }

    @Override
    public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException {
        return v.visit(this);
    }
}