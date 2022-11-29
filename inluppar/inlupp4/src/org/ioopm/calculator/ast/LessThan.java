package org.ioopm.calculator.ast;

import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.Visitor;

/**
 * LessThan
 */
public class LessThan  extends ConditionalOperator{

	public LessThan(SymbolicExpression lhs, SymbolicExpression rhs) {
		super("LessThan", lhs, rhs);
	}

	@Override
	public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException {
		return v.visit(this);
	}
    
}