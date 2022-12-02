package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.NonConstantVariableException;

/**
 * Named constant node
 */
public class NamedConstant extends Constant {
    /** The name of the constant */
    private String name;

    public NamedConstant(String name, double value) {
        super(value);
        this.name = name;
    }

    /**
     * @return String representation of the named constant
     */
    @Override
    public String toString() {
        return name;
    }

    @Override
    public boolean equals(Object other) {
        if (other instanceof NamedConstant) {
            return equals((NamedConstant) other);
        }
        return false;
    }

    private boolean equals(NamedConstant other) {
        return this.getValue() == other.getValue() && this.name.equals(other.name);
    }

    @Override
    public SymbolicExpression accept(Visitor v)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        return v.visit(this);
    }
}