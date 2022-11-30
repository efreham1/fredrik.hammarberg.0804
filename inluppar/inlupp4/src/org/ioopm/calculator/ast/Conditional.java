package org.ioopm.calculator.ast;

import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.NonConstantVariableException;
import org.ioopm.calculator.Visitor;

/**
 * Conditional
 */
public class Conditional extends SymbolicExpression{
    private SymbolicExpression conditionalOperator;
    private SymbolicExpression ifScope;
    private SymbolicExpression elseScope;

    public Conditional(SymbolicExpression conditionalOperator, SymbolicExpression ifScope, SymbolicExpression elseScope) {
        super("Conditional");
		this.conditionalOperator = conditionalOperator;
		this.ifScope = ifScope;
		this.elseScope = elseScope;
    }

    public SymbolicExpression getIfScope(){
        return ifScope;
    }
    public SymbolicExpression getElseScope(){
        return elseScope;
    }
    public SymbolicExpression getConditionalOperator(){
        return conditionalOperator;
    }

    @Override
    public String toString() {
        return "if " + conditionalOperator+ " " + ifScope + " else " + elseScope;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Conditional){
            return equals((Conditional) obj);
        }
        return false;
    }

    public boolean equals(Conditional c){
        return conditionalOperator.equals(c.conditionalOperator) && ifScope.equals(c.ifScope) && elseScope.equals(c.elseScope);
    }

	@Override
	public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException,
			NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return v.visit(this);
	}

    
}