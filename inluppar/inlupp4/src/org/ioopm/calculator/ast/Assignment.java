package org.ioopm.calculator.ast;

import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.NonConstantVariableException;
import org.ioopm.calculator.Visitor;

public class Assignment extends Binary {
    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super("Assignment", lhs, rhs);
    }

    /**
     * @return String representation for the operation
     */
    @Override
    public String getName() {
        return "=";
    }

    @Override
    public SymbolicExpression accept(Visitor v)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        return v.visit(this);
    }
}