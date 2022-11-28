package org.ioopm.calculator.ast;

/**
* Abstract class for binary operation nodes
*/
public abstract class Binary extends SymbolicExpression {
    /** The left hand side of the operation */
    protected SymbolicExpression lhs = null;
    /** The right hand side of the operation */
    protected SymbolicExpression rhs = null;

    /**
    * @param name The name of the operation
    * @param lhs The left hand side of the operation
    * @param rhs The right hand side of the operation
    */
    public Binary(String name, SymbolicExpression lhs, SymbolicExpression rhs) {
        super(name, lhs, rhs);
        this.lhs = lhs;
        this.rhs = rhs;
    }

    /**
    * The string representation of the operation and it's arguments.
    * Subexpressions with a lower priority will be surrounded by parenthesis.
    */
    @Override
    public String toString() {
        String result = "";
        if ( lhs.getPriority() < this.getPriority() ) {
            result += "(" + lhs + ")";
        } else {
            result += lhs;
        }
        result += " " + this.getName() + " ";
        if ( rhs.getPriority() < this.getPriority() ) {
            result += "(" + rhs + ")";
        } else {
            result += rhs;
        }
        return result;
    }

    @Override
    public boolean equals(Object other) {
        if(other instanceof Binary) {
            return equals((Binary) other);
        }
        return false;
    }

    private boolean equals(Binary other) {
        return this.getName().equals(other.getName())
               && this.lhs.equals(other.lhs)
               && this.rhs.equals(other.rhs);
    }

    public SymbolicExpression lhs(){
        return lhs;
    }
    
    public SymbolicExpression rhs(){
        return rhs;
    }
}