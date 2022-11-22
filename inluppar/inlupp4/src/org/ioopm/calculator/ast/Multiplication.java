package org.ioopm.calculator.ast;

/**
* Multiplication node
*/
public class Multiplication extends Binary {
    public Multiplication(SymbolicExpression leftFactor, SymbolicExpression rightFactor) {
        super("Multiplication", leftFactor, rightFactor);
    }

    /**
    * @return String representation for the operation
    */
    public String getName() {
        return "*";
    }

    /**
    * Get the priority of the operation
    *
    * @return an int representing the priority of the operation
    */
    public int getPriority() {
        return 1;
    }

    /**
    * Reduces a SymbolicExpression as far as possible and evaluates it.
    *
    * If both the left hand side and the right hand side of the multiplication
    * are constant values, their product is returned as a Constant
    *
    * @param vars The Environment in which the variables exist
    * @return the product of lhs and rhs
    */
    public SymbolicExpression eval(Environment vars) throws IllegalExpressionException, DivisionByZeroException {
        SymbolicExpression leftFactor = this.lhs.eval(vars);
        SymbolicExpression rightFactor = this.rhs.eval(vars);
        if(leftFactor.isConstant() && rightFactor.isConstant()) {
            return new Constant(leftFactor.getValue() * rightFactor.getValue());
        } else {
            return new Multiplication(leftFactor, rightFactor);
        }
    }
}