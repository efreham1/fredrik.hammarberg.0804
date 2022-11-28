package org.ioopm.calculator.ast;

import org.ioopm.calculator.Visitor;

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
	public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException {
		return v.visit(this);
	}
}