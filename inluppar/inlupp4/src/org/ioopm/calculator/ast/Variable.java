package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;

public class Variable extends Atom implements Comparable<Variable>{
    private String identifier;

    public Variable(String identifier) {
        super("Variable");
        this.identifier = identifier;
    }

    @Override
    public String toString() {
        return identifier;
    }

    @Override
    public boolean equals(Object other) {
        if(other instanceof Variable) {
            return equals((Variable) other);
        }
        return false;
    }

    private boolean equals(Variable other) {
        return identifier.equals(other.identifier);
    }

    @Override
    public final int hashCode() {
        return identifier.hashCode();
    }

	@Override
	public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException {
		return v.visit(this);
	}

    @Override
    public int compareTo(Variable o) {
        return identifier.compareTo(o.identifier);
    }
}