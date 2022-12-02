package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.NonConstantVariableException;

/**
 * Logarithm node
 */
public class Log extends Unary {
    public Log(SymbolicExpression arg) {
        super("Log", arg);
    }

    /**
     * @return String representation for the operation
     */
    @Override
    public String getName() {
        return "Log";
    }

    @Override
    public SymbolicExpression accept(Visitor v)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        return v.visit(this);
    }
}