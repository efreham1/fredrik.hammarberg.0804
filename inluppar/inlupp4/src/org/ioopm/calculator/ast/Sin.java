package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;

/**
* Sine node
*/
public class Sin extends Unary {    
    public Sin(SymbolicExpression arg) {
        super("Sin", arg);
    }

    /**
    * @return String representation for the operation
    */
    @Override
    public String getName() {
        return "Sin";
    }

	@Override
	public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException {
		return v.visit(this);
	}
}