package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.NonConstantVariableException;

/**
 * Sine node
 */
public class Sin extends Unary {
    public Sin(SymbolicExpression arg) {
        super("Sin", arg);
    }

    /**
     * @return String representation for the operation
     */
    @Override
    public String getName() {
        return "Sin";
    }

    @Override
    public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException,
            NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException,
            NonConstantVariableException, NamedConstantAssignmentException, ReassignmentException,
            RootEnvironmentException, NonConstantVariableException {
        return v.visit(this);
    }
}