package org.ioopm.calculator.ast;

/**
* Exp node
*/
public class Exp extends Unary {
    public Exp(SymbolicExpression arg) {
        super("Exp", arg);
    }

    /**
    * @return String representation for the operation
    */
    public String getName() {
        return "exp";
    }

    /**
    * Reduces a SymbolicExpression as far as possible and evaluates it.
    *
    * If the argument of the function is a constant value, the value
    * e^arg is returned
    *
    * @param vars The Environment in which the variables exist
    * @return the value of e^arg
    */
    public SymbolicExpression eval(Environment vars) throws IllegalExpressionException, DivisionByZeroException {
        SymbolicExpression arg = this.arg.eval(vars);
        if (arg.isConstant()) {
            return new Constant(Math.exp(arg.getValue()));
        } else {
            return new Exp(arg);
        }
    }
}