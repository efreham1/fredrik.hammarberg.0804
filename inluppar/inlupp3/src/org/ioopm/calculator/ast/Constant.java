package org.ioopm.calculator.ast;

/**
* Constant node
*/
public class Constant extends Atom {
    /** Double representation of the Constant's value */
    private double value;

    public Constant(double value) {
        super("Constant");
        this.value = value;
    }

    public boolean isConstant() {
        return true;
    }

    public double getValue() {
        return value;
    }

    public String toString() {
        if(value - (int) value == 0) {
            return String.valueOf((int) value);
        }
        return String.valueOf(this.value);
    }

    public boolean equals(Object other) {
        if(other instanceof Constant) {
            return equals((Constant) other);
        }
        return false;
    }

    private boolean equals(Constant other) {
        return value == other.value;
    }

    /**
    * Returns `this`, as a Constant does not need to be further evaluated
    *
    * @param vars The Environment in which the variables exist
    * @return `this`
    */
    public Constant eval(Environment vars) {
        return this;
    }
}