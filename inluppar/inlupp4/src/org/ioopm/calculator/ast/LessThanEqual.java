package org.ioopm.calculator.ast;

import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.NonConstantVariableException;
import org.ioopm.calculator.Visitor;

/**
 * LessThanEqual
 */
public class LessThanEqual extends ConditionalOperator {

	public LessThanEqual(SymbolicExpression lhs, SymbolicExpression rhs) {
		super("LessThanEqual", lhs, rhs);
	}

	@Override
	public String getName() {
		return "<=";
	}

	@Override
	public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return v.visit(this);
	}

}