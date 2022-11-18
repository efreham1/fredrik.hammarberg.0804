package org.ioopm.calculator.ast;

/**
* Cosine node
*/
public class Cos extends Unary {
    public Cos(SymbolicExpression arg) {
        super("Cos", arg);
    }

    /**
    * @return String representation for the operation
    */
    public String getName() {
        return "cos";
    }

    /**
    * Reduces a SymbolicExpression as far as possible and evaluates it.
    *
    * If the argument of the function is a constant value, the cosine
    * of the argument is returned.
    *
    * @param vars The Environment in which the variables exist
    * @return the cosine of arg
    */
    public SymbolicExpression eval(Environment vars) throws IllegalExpressionException, DivisionByZeroException {
        SymbolicExpression arg = this.arg.eval(vars);
        if (arg.isConstant()) {
            return new Constant(Math.cos(arg.getValue()));
        } else {
            return new Cos(arg);
        }
    }
}