package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;

/**
* Cosine node
*/
public class Cos extends Unary {
    public Cos(SymbolicExpression arg) {
        super("Cos", arg);
    }

    /**
    * @return String representation for the operation
    */
    @Override
    public String getName() {
        return "Cos";
    }
    
    @Override
    public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException {
        return v.visit(this);
    }
}