package org.ioopm.calculator.ast;

/**
 * ConditionalOperator
 */
public abstract class ConditionalOperator extends Binary{

	public ConditionalOperator(String name, SymbolicExpression lhs, SymbolicExpression rhs) {
		super(name, lhs, rhs);
	}
}