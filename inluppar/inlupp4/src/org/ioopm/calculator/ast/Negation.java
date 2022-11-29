package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;

public class Negation extends Unary {    
    public Negation(SymbolicExpression arg) {
        super("Negation", arg);
    }

    /**
    * @return String representation for the operation
    */
    @Override
    public String getName() {
        return "-";
    }

    @Override
    public String toString() {
        if(arg.getPriority() > 0) {
            return "-" + arg;
        }
        return super.toString();
    }

    @Override
    public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException {
        return v.visit(this);
    }
}