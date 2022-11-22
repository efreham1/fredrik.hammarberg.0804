package org.ioopm.calculator.ast;

public class Variable extends Atom {
    private String identifier;

    public Variable(String identifier) {
        super("Variable");
        this.identifier = identifier;
    }

    public String toString() {
        return identifier;
    }

    public boolean equals(Object other) {
        if(other instanceof Variable) {
            return equals((Variable) other);
        }
        return false;
    }

    private boolean equals(Variable other) {
        return identifier.equals(other.identifier);
    }

    @Override
    public final int hashCode() {
        return identifier.hashCode();
    }

    public SymbolicExpression eval(Environment vars) throws IllegalExpressionException {
        SymbolicExpression value = vars.get(this);
        return value == null ? this : value;
    }
}