package org.ioopm.calculator.ast;

/**
* Sine node
*/
public class Sin extends Unary {    
    public Sin(SymbolicExpression arg) {
        super("Sin", arg);
    }

    /**
    * @return String representation for the operation
    */
    public String getName() {
        return "Sin";
    }

    /**
    * Reduces a SymbolicExpression as far as possible and evaluates it.
    *
    * If the argument of the function is a constant value, the sine
    * of the argument is returned.
    *
    * @param vars The Environment in which the variables exist
    * @return the sine of arg
    */
    public SymbolicExpression eval(Environment vars) throws IllegalExpressionException, DivisionByZeroException {
        SymbolicExpression arg = this.arg.eval(vars);
        if (arg.isConstant()) {
            return new Constant(Math.sin(arg.getValue()));
        } else {
            return new Sin(arg);
        }
    }
}