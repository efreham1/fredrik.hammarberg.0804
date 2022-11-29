package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;

public class NamedConstantChecker implements Visitor {
    
    public boolean check(SymbolicExpression topLevel) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
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
		n.rhs().accept(this);
        if (n.rhs().isConstant()) {
            throw new NamedConstantAssignmentException("Error, assignment to constant: "+ n);
        }
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