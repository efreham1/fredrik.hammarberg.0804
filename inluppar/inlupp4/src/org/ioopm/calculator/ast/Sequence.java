package org.ioopm.calculator.ast;

import java.util.LinkedList;

import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.NonConstantVariableException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.Visitor;

/**
 * Sequence
 */
public class Sequence extends SymbolicExpression{
    private LinkedList<SymbolicExpression> functionSteps = new LinkedList<>();

	public Sequence() {
		super("Sequence");
	}

    public void addStep(SymbolicExpression step){
        this.functionSteps.add(step);
    }

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		for (SymbolicExpression step : functionSteps){
			sb.append(step);
			sb.append("\n");
		}
		sb.deleteCharAt(sb.length()-1);
		return sb.toString();
	}

	public LinkedList<SymbolicExpression> getFunctionSteps(){
		return functionSteps;
	}

	@Override
    public boolean equals(Object other) {
        if(other instanceof Sequence) {
            return equals((Sequence) other);
        }
        return false;
    }

    private boolean equals(Sequence other) {
		int i = 0;
		for (SymbolicExpression step : functionSteps) {
			if(!(step.equals(other.functionSteps.get(i++)))) {
				return false;
			}
		}
		return true;
    }

	public boolean isEmpty(){
		return functionSteps.isEmpty();
	}

	@Override
	public SymbolicExpression accept(Visitor v)
			throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
			ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return v.visit(this);
	}

    
}