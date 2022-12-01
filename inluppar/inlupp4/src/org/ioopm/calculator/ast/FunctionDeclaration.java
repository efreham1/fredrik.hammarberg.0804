package org.ioopm.calculator.ast;

import java.util.LinkedList;

import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.NonConstantVariableException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.Visitor;

/**
 * FunctionDeclaration
 */
public class FunctionDeclaration extends SymbolicExpression {
    private LinkedList<Variable> arguments;
    private String name;

	public FunctionDeclaration(String name, LinkedList<Variable> arguments) {
		super(name);
        this.name = name;
		this.arguments = arguments;
	}

    public LinkedList<Variable> getArguments(){
        return this.arguments;
    }

    @Override
    public boolean equals(Object other) {
        if(other instanceof FunctionDeclaration) {
            return equals((FunctionDeclaration) other);
        }
        return false;
    }

    private boolean equals(FunctionDeclaration other) {
        if (this.name.equals(other.name)) {
            int i = 0;
            for (Variable arg : arguments) {
                if(!(arg.equals(other.arguments.get(i++)))) {
                    return false;
                }
            }
            return true;
        } else {
            return false;
        }
    }

    @Override
    public String toString() {
        String result = "";
        StringBuilder sb = new StringBuilder(result);
        sb.append(this.name);
        sb.append("(");
        for (Variable arg : arguments) {
            sb.append(arg + ", ");
        }
        sb.delete(sb.length()-2, sb.length());
        sb.append(")");
        return sb.toString();
    }

    @Override
    public String getName(){
        return this.name;
    }
    
	@Override
	public SymbolicExpression accept(Visitor v)
			throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
			ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return v.visit(this);
	}

    
}