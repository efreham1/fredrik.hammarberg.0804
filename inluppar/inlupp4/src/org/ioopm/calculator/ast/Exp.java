package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.NonConstantVariableException;

/**
 * Exp node
 */
public class Exp extends Unary {
    public Exp(SymbolicExpression arg) {
        super("Exp", arg);
    }

    /**
     * @return String representation for the operation
     */
    @Override
    public String getName() {
        return "Exp";
    }

    @Override
    public SymbolicExpression accept(Visitor v)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        return v.visit(this);
    }
}