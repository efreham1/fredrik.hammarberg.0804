package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;

public class NamedConstantChecker implements Visitor {

	public boolean check(SymbolicExpression topLevel) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		topLevel.accept(this);
		return true;
	}

	@Override
	public SymbolicExpression visit(Addition n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		n.lhs().accept(this);
		n.rhs().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Assignment n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		n.lhs().accept(this);
		if (n.rhs().isConstant()) {
			throw new NamedConstantAssignmentException("Error, assignment to constant: " + n);
		}
		return n;
	}

	@Override
	public SymbolicExpression visit(Clear n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return n;
	}

	@Override
	public SymbolicExpression visit(Constant n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return n;
	}

	@Override
	public SymbolicExpression visit(Cos n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		n.arg().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Division n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		n.lhs().accept(this);
		n.rhs().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Exp n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		n.arg().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Log n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		n.arg().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Multiplication n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		n.lhs().accept(this);
		n.rhs().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(NamedConstant n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return n;
	}

	@Override
	public SymbolicExpression visit(Negation n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		n.arg().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Quit n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return n;
	}

	@Override
	public SymbolicExpression visit(Sin n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		n.arg().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Subtraction n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		n.lhs().accept(this);
		n.rhs().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Variable n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return n;
	}

	@Override
	public SymbolicExpression visit(Vars n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return n;
	}

	@Override
	public SymbolicExpression visit(Scope n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		n.arg().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Conditional n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		n.getIfScope().accept(this);
		n.getElseScope().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Equal n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return n;
	}

	@Override
	public SymbolicExpression visit(GreaterThan n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return n;
	}

	@Override
	public SymbolicExpression visit(GreaterThanEqual n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return n;
	}

	@Override
	public SymbolicExpression visit(LessThan n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return n;
	}

	@Override
	public SymbolicExpression visit(LessThanEqual n) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return n;
	}
}