package org.ioopm.calculator.ast;

/**
* Assignment node
*/
public class Assignment extends Binary {
    public Assignment(SymbolicExpression lhs, SymbolicExpression rhs) {
        super("Assignment", lhs, rhs);
    }

    /**
    * @return String representation for the operation
    */
    public String getName() {
        return "="; 
    }

    /**
    * Evaluates the left hand side expression and attempts to assign it to the
    * right hand side expression
    *
    * @param vars The Environment in which the variables exist
    * @throws IllegalExpressionException if the right hand side is a named constant
    * @return the evaluation of the left hand side expression
    */
    public SymbolicExpression eval(Environment vars) throws IllegalExpressionException, DivisionByZeroException {
        SymbolicExpression left = lhs.eval(vars);
        if (rhs.isConstant()){
            throw new IllegalExpressionException("Error: Cannot redefine named constant '" + rhs + "'");
        }
        else {
            vars.put((Variable) rhs, left);
            return left;
        }
    }
}