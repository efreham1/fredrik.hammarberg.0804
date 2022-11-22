package org.ioopm.calculator.ast;

/**
* Logarithm node
*/
public class Log extends Unary {
    public Log(SymbolicExpression arg) {
        super("Log", arg);
    }

    /**
    * @return String representation for the operation
    */
    public String getName() {
        return "Log";
    }

    /**
    * Reduces a SymbolicExpression as far as possible and evaluates it.
    *
    * If the argument of the function is a constant value, the natural logarithm
    * of the argument is returned.
    *
    * @param vars The Environment in which the variables exist
    * @return the natural logarithm of arg
    */
    public SymbolicExpression eval(Environment vars) throws IllegalExpressionException, DivisionByZeroException{
        SymbolicExpression arg = this.arg.eval(vars);
        if (arg.isConstant()) {
            if (arg.getValue()<=0){
                throw new IllegalExpressionException("The Logarithm of a number blow or equal to zero is undefined");
            }
            return new Constant(Math.log(arg.getValue()));
        } else {
            return new Log(arg);
        }
    }
}