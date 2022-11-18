package org.ioopm.calculator.ast;

/**
* Named constant node
*/
public class NamedConstant extends Constant {
    /**The name of the constant*/
    private String name;

    public NamedConstant(String name, double value){
        super(value);
        this.name = name;
    }

    /**
    * @return String representation of the named constant
    */
    public String toString() {
        return name;
    }

    public boolean equals(Object other) {
        if(other instanceof NamedConstant) {
            return equals((NamedConstant) other);
        }
        return false;
    }

    private boolean equals(NamedConstant other) {
        return this.getValue() == other.getValue() && this.name.equals(other.name);
    }

    /**
    * The value of the named constant
    *
    * @return the value of the constant as a Constant type
    */
    public Constant eval(Environment vars) {
        return new Constant(this.getValue());
    }
}