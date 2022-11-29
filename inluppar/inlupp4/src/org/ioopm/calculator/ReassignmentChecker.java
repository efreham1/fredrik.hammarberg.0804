package org.ioopm.calculator;

import java.util.LinkedList;

import org.ioopm.calculator.ast.*;

public class ReassignmentChecker implements Visitor {
	LinkedList<String> varlist = new LinkedList<String>();
    
    public boolean check(SymbolicExpression topLevel) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException{
        varlist.clear();
		topLevel.accept(this);
        return true;
    }

	@Override
	public SymbolicExpression visit(Addition n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		n.lhs().accept(this);
        n.rhs().accept(this);
        return n;
	}

	@Override
	public SymbolicExpression visit(Assignment n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		if (varlist.contains(n.rhs().toString())) {
			throw new ReassignmentException("Error, the variable " + n.rhs() + " is reassigned.");
		}
		varlist.add(n.rhs().toString());
        return n;
	}

	@Override
	public SymbolicExpression visit(Clear n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		return n;
	}

	@Override
	public SymbolicExpression visit(Constant n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		return n;
	}

	@Override
	public SymbolicExpression visit(Cos n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		n.arg().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Division n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		n.lhs().accept(this);
        n.rhs().accept(this);
        return n;
	}

	@Override
	public SymbolicExpression visit(Exp n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		n.arg().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Log n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		n.arg().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Multiplication n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		n.lhs().accept(this);
        n.rhs().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(NamedConstant n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		return n;
	}

	@Override
	public SymbolicExpression visit(Negation n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		n.arg().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Quit n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		return n;
	}

	@Override
	public SymbolicExpression visit(Sin n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		n.arg().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Subtraction n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		n.lhs().accept(this);
        n.rhs().accept(this);
		return n;
	}

	@Override
	public SymbolicExpression visit(Variable n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		return n;
	}

	@Override
	public SymbolicExpression visit(Vars n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
		return n;
	}
}