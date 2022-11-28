package org.ioopm.calculator.ast;

/**
* Abstract class for unary operation nodes
*/
public abstract class Unary extends SymbolicExpression {
    protected SymbolicExpression arg = null;

    public Unary(String name, SymbolicExpression arg) {
        super(name, arg);
        this.arg = arg;
    }

    /**
    * The string representation of the operation, with the argument inside of parenthesis
    */
    @Override
    public String toString() {
        String result = "";
        StringBuilder sb = new StringBuilder(result);
        sb.append(this.getName());
        sb.append("(");
        sb.append(this.arg);
        sb.append(")");
        return sb.toString();
    }

    @Override
    public int getPriority() {
        return 2;
    }

    @Override
    public boolean equals(Object other) {
        if(other instanceof Unary) {
            return equals((Unary) other);
        }
        return false;
    }

    private boolean equals(Unary other) {
        return this.getName().equals(other.getName()) && this.arg.equals(other.arg);
    }

    public SymbolicExpression arg(){
        return arg;
    }
}