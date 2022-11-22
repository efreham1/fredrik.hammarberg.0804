package org.ioopm.calculator.ast;

/**
* Negation node
*/
public class Negation extends Unary {    
    public Negation(SymbolicExpression arg) {
        super("Negation", arg);
    }

    /**
    * @return String representation for the operation
    */
    public String getName() {
        return "-";
    }

    public String toString() {
        if(arg.getPriority() > 0) {
            return "-" + arg;
        }
        return super.toString();
    }

    public SymbolicExpression eval(Environment vars) throws IllegalExpressionException, DivisionByZeroException {
        SymbolicExpression arg = this.arg.eval(vars);
        if(arg.isConstant()) {
            return new Constant(-arg.getValue());
        } else if(arg instanceof Negation) {
            return ((Negation) arg).arg;
        } else {
            return new Negation(arg);
        }
    }
}