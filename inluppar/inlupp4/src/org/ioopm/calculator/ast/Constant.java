package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;

/**
 * Constant node
 */
public class Constant extends Atom {
    /** Double representation of the Constant's value */
    private double value;

    public Constant(double value) {
        super("Constant");
        this.value = value;
    }
    
    @Override
    public boolean isConstant() {
        return true;
    }

    @Override
    public double getValue() {
        return value;
    }

    @Override
    public String toString() {
        if (value - (int) value == 0) {
            return String.valueOf((int) value);
        }
        return String.valueOf(this.value);
    }

    @Override
    public boolean equals(Object other) {
        if (other instanceof Constant) {
            return equals((Constant) other);
        }
        return false;
    }

    private boolean equals(Constant other) {
        if (other instanceof NamedConstant) {
            return false;
        }
        return value == other.value;
    }

    @Override
    public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException {
        return v.visit(this);
    }
}