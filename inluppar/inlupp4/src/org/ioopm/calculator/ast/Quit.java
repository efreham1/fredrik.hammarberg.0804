package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;

/**
* Quit command node
*/
public class Quit extends Command {
    private static final Quit theInstance = new Quit();

    private Quit() {
        super("Quit");
    }

    public static Quit instance() {
        return theInstance;
    }

	@Override
	public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException {
		return v.visit(this);
	}
}