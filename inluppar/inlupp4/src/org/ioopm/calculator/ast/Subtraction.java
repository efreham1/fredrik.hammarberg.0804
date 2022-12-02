package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.NonConstantVariableException;

public class Subtraction extends Binary {
    public Subtraction(SymbolicExpression leftTerm, SymbolicExpression rightTerm) {
        super("Subtraction", leftTerm, rightTerm);
    }

    /**
     * Get the priority of the operation
     *
     * @return an int representing the priority of the operation
     */
    @Override
    public int getPriority() {
        return 0;
    }

    /**
     * @return String representation for the operation
     */
    @Override
    public String getName() {
        return "-";
    }

    @Override
    public SymbolicExpression accept(Visitor v)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        return v.visit(this);
    }
}