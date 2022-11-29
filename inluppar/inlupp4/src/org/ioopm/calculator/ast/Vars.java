package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;

public class Vars extends Command {
    private static final Vars theInstance = new Vars();
    
    private Vars() {
        super("Vars");
    }

    public static Vars instance() {
        return theInstance;
    }

    @Override
    public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException {
        return v.visit(this);
    }
}