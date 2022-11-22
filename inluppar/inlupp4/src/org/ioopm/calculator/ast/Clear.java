package org.ioopm.calculator.ast;

/**
* Clear command node
*/
public class Clear extends Command {
    private static final Clear theInstance = new Clear();

    private Clear() {
        super("Clear");
    }

    public static Clear instance() {
        return theInstance;
    }

    public SymbolicExpression eval(Environment vars) {
        throw new RuntimeException("Commands may not be evaluated.");
    }
}