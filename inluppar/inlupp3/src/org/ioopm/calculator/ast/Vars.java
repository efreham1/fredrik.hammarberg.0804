package org.ioopm.calculator.ast;

/**
* Vars command node
*/
public class Vars extends Command {
    private static final Vars theInstance = new Vars();
    
    private Vars() {
        super("Vars");
    }

    public static Vars instance() {
        return theInstance;
    }

    public SymbolicExpression eval(Environment vars) {
        throw new RuntimeException("Commands may not be evaluated.");
    }
}