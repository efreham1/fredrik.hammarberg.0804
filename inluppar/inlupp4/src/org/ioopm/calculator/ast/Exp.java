package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
/**
* Exp node
*/
public class Exp extends Unary {
    public Exp(SymbolicExpression arg) {
        super("Exp", arg);
    }

    /**
    * @return String representation for the operation
    */
    @Override
    public String getName() {
        return "Exp";
    }

    @Override
    public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException{
        return v.visit(this);
    }
}