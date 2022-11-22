package org.ioopm.calculator.ast;

/**
* Subtraction node
*/
public class Subtraction extends Binary {
    public Subtraction(SymbolicExpression leftTerm, SymbolicExpression rightTerm) {
        super("Subtraction", leftTerm, rightTerm);
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
        return "-";
    }

    /**
    * Reduces a SymbolicExpression as far as possible and evaluates it.
    *
    * If both the left hand side and the right hand side of the subtraction
    * are constant values, the difference is returned as a Constant
    *
    * @param vars The Environment in which the variables exist
    * @return the difference of lhs and rhs
    */
    public SymbolicExpression eval(Environment vars) throws IllegalExpressionException, DivisionByZeroException {
        SymbolicExpression leftTerm = this.lhs.eval(vars);
        SymbolicExpression rightTerm = this.rhs.eval(vars);
        if(leftTerm.isConstant() && rightTerm.isConstant()) {
            return new Constant(leftTerm.getValue() - rightTerm.getValue());
        } else {
            return new Subtraction(leftTerm, rightTerm);
        }
    }
}