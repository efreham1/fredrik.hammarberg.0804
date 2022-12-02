package org.ioopm.calculator.ast;

import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.NonConstantVariableException;
import org.ioopm.calculator.Visitor;

/**
 * GreaterThanEqual
 */
public class GreaterThanEqual extends ConditionalOperator{

	public GreaterThanEqual(SymbolicExpression lhs, SymbolicExpression rhs) {
		super("GreaterThanEqual", lhs, rhs);
	}

	@Override
	public String getName(){
		return ">=";
	}

	@Override
	public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return v.visit(this);
	}

    
}