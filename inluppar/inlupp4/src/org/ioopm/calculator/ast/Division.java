package org.ioopm.calculator.ast;

/**
* Division node
*/
public class Division extends Binary {

    public Division(SymbolicExpression numerator, SymbolicExpression denominator) {
        super("Division", numerator, denominator);
    }

    /**
    * @return String representation for the operation
    */
    public String getName() {
        return "/";
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
    * If both the left hand side and the right hand side of the division
    * are constant values, the ratio is returned as a Constant
    *
    * @param vars The Environment in which the variables exist
    * @return the ratio of lhs and rhs
    * @throws DivisionByZeroException if denominator is zero
    */
    public SymbolicExpression eval(Environment vars) throws IllegalExpressionException, DivisionByZeroException {
        SymbolicExpression numerator = this.lhs.eval(vars);
        SymbolicExpression denominator = this.rhs.eval(vars);
        if(numerator.isConstant() && denominator.isConstant()) {
            if(Math.abs(denominator.getValue()) < 1e-15) {
                throw new DivisionByZeroException("Division by 0 is undefined");
            }
            return new Constant(numerator.getValue() / denominator.getValue());
        } else {
            return new Division(numerator, denominator);
        }
    }
}