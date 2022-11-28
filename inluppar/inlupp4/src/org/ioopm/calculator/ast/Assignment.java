package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;

public class Assignment extends Binary {
    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super("Assignment", lhs, rhs);
    }

    /**
    * @return String representation for the operation
    */
    @Override
    public String getName() {
        return "="; 
    }

    @Override
    public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException {
        return v.visit(this);
    }
}