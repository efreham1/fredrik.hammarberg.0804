package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;

/**
* Cosine node
*/
public class Cos extends Unary {
    public Cos(SymbolicExpression arg) {
        super("Cos", arg);
    }

    /**
    * @return String representation for the operation
    */
    @Override
    public String getName() {
        return "Cos";
    }
    
    @Override
    public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException {
        return v.visit(this);
    }
}