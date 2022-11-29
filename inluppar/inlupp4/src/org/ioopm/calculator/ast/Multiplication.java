package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;

/**
* Multiplication node
*/
public class Multiplication extends Binary {
    public Multiplication(SymbolicExpression leftFactor, SymbolicExpression rightFactor) {
        super("Multiplication", leftFactor, rightFactor);
    }

    /**
    * @return String representation for the operation
    */
    @Override
    public String getName() {
        return "*";
    }

    /**
    * Get the priority of the operation
    *
    * @return an int representing the priority of the operation
    */
    @Override
    public int getPriority() {
        return 1;
    }

	@Override
	public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException {
		return v.visit(this);
	}

}