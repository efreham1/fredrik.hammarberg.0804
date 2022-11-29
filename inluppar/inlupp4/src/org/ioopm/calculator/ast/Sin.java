package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;

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
	public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException {
		return v.visit(this);
	}
}