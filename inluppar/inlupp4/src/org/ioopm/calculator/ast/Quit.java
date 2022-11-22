package org.ioopm.calculator.ast;

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

    public SymbolicExpression eval(Environment vars) {
        throw new RuntimeException("Commands may not be evaluated.");
    }
}