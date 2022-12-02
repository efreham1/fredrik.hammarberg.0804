package org.ioopm.calculator.ast;

import java.util.LinkedList;

import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.NonConstantVariableException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.Visitor;

/**
 * FunctionCall
 */
public class FunctionCall extends SymbolicExpression {
	private String functionName;
	private LinkedList<Atom> arguments;

	public FunctionCall(String functionName, LinkedList<Atom> arguments) {
		super(functionName);
		this.functionName = functionName;
		this.arguments = arguments;
	}

	public String getFunctionName() {
		return functionName;
	}

	public LinkedList<Atom> getArguments() {
		return arguments;
	}

	@Override
	public String toString() {
		String result = "";
		StringBuilder sb = new StringBuilder(result);
		sb.append(this.functionName);
		sb.append("(");
		for (Atom arg : arguments) {
			sb.append(arg + ", ");
		}
		if (arguments.size() > 0) {
			sb.delete(sb.length() - 2, sb.length());
		}
		sb.append(")");
		return sb.toString();
	}

	@Override
	public SymbolicExpression accept(Visitor v)
			throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
			ReassignmentException, RootEnvironmentException, NonConstantVariableException {
		return v.visit(this);
	}

}