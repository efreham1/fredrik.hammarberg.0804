package org.ioopm.calculator.ast;

/**
* Addition node
*/
public class Addition extends Binary {
    public Addition(SymbolicExpression leftTerm, SymbolicExpression rightTerm) {
        super("Addition", leftTerm, rightTerm);
    }

    /**
    * Get the priority of the operation
    *
    * @return an int representing the priority of the operation
    */
    public int getPriority() {
        return 0;
    }

    /**
    * @return String representation for the operation
    */
    public String getName() {
        return "+";
    }

    /**
    * Reduces a SymbolicExpression as far as possible and evaluates it.
    *
    * If both the left hand side and the right hand side of the addition
    * are constant values, their sum is returned as a Constant
    *
    * @param vars The Environment in which the variables exist
    * @return the sum of lhs and rhs
    */
    public SymbolicExpression eval(Environment vars) throws IllegalExpressionException, DivisionByZeroException {
        SymbolicExpression left = this.lhs.eval(vars);
        SymbolicExpression right = this.rhs.eval(vars);
        if(left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() + right.getValue());
        } else {
            return new Addition(left, right);
        }
    }
}