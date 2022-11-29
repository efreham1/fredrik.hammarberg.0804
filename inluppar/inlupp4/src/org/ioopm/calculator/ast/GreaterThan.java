package org.ioopm.calculator.ast;

import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.Visitor;

/**
 * GreaterThan
 */
public class GreaterThan  extends ConditionalOperator{

	public GreaterThan(SymbolicExpression lhs, SymbolicExpression rhs) {
		super("GreaterThan", lhs, rhs);
	}

	@Override
	public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException {
		return v.visit(this);
	}

    
}