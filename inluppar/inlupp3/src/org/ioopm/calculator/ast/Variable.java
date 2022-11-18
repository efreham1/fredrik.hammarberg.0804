package org.ioopm.calculator.ast;

/**
* Variable node
*/
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

    private boolean equals(SymbolicExpression other) {
        return hashCode() == other.hashCode();
    }

    public SymbolicExpression eval(Environment vars) throws IllegalExpressionException {
        SymbolicExpression value = vars.get(this);
        return value == null ? this : value;
    }

    public int hashCode() {
        return identifier.hashCode();
    }
}