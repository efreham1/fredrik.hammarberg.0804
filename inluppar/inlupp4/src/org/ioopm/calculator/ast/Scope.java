package org.ioopm.calculator.ast;

import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.Visitor;

public class Scope extends Unary {
    
    public Scope(SymbolicExpression arg){
        super("Scope", arg);
    }

    @Override
    public String toString(){
        return "{"+ this.arg +"}";
    }

    @Override
    public String getName(){
        return "Scope";
    }

    @Override
    public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException {
        return v.visit(this);
    }

}