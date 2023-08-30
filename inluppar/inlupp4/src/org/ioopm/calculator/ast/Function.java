package org.ioopm.calculator.ast;

import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.NonConstantVariableException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.Visitor;

public class Function extends SymbolicExpression {
    private FunctionDeclaration fDeclaration;
    private Sequence functionBody;

    public Function(FunctionDeclaration fDeclaration, Sequence functionBody){
        super(fDeclaration.getName());
        this.fDeclaration = fDeclaration;
        this.functionBody = functionBody;
    }

    public FunctionDeclaration getFDeclaration(){
        return fDeclaration;
    }

    public Sequence getFunctionBody(){
        return functionBody;
    }

    @Override
    public SymbolicExpression accept(Visitor v)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        throw new FunctionVisitException("Error: visited a non-used node, function!");
    }
}
