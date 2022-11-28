package org.ioopm.calculator;
import org.ioopm.calculator.ast.*;

public class EvaluationVisitor implements Visitor {
    private Environment env = null;

    public SymbolicExpression evaluate(SymbolicExpression topLevel, Environment env) throws IllegalExpressionException, DivisionByZeroException{
        this.env = env;
        return topLevel.accept(this);
    }

    // This method gets called from Addition.accept(Visitor v) -- you should
    // be able to see from the eval() methods how these should behave (i.e., 
    // compare this method with your Addition::eval() and Symbolic.addition) 
    public SymbolicExpression visit(Addition n) throws IllegalExpressionException, DivisionByZeroException {
        // Visit the left hand side and right hand side subexpressions
        SymbolicExpression left = n.lhs().accept(this);
        SymbolicExpression right = n.rhs().accept(this);
        // When we come back here, the visitor has visited all subexpressions, 
        // meaning left and right point to newly created trees reduced to 
        // the extent possible (best case -- both are constants)

        // If subexpressions are fully evaluated, replace them in
        // the tree with a constant whose value is the sub of the
        // subexpressions, if not, simply construct a new addition
        // node from the new subexpressions
        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() + right.getValue());
        } else {
            return new Addition(left, right);
        }
    }

    @Override
    public SymbolicExpression visit(Assignment n) throws IllegalExpressionException, DivisionByZeroException{
        SymbolicExpression left = n.lhs().accept(this);
        if (n.rhs().isConstant()){
            throw new IllegalExpressionException("Error: Cannot redefine named constant '" + n.rhs() + "'");
        }
        else {
            env.put((Variable) n.rhs(), left);
            return left;
        }
    }

    @Override
    public SymbolicExpression visit(Constant n) throws IllegalExpressionException, DivisionByZeroException{
        return n;
    }

    @Override
    public SymbolicExpression visit(Cos n) throws IllegalExpressionException, DivisionByZeroException{
        SymbolicExpression arg = n.arg().accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.cos(arg.getValue()));
        } else {
            return new Cos(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Division n) throws IllegalExpressionException, DivisionByZeroException{
        SymbolicExpression numerator = n.lhs().accept(this);
        SymbolicExpression denominator = n.rhs().accept(this);
        if(numerator.isConstant() && denominator.isConstant()) {
            if(Math.abs(denominator.getValue()) < 1e-15) {
                throw new DivisionByZeroException("Division by 0 is undefined");
            }
            return new Constant(numerator.getValue() / denominator.getValue());
        } else {
            return new Division(numerator, denominator);
        }
    }

    @Override
    public SymbolicExpression visit(Exp n) throws IllegalExpressionException, DivisionByZeroException{
        SymbolicExpression arg = n.arg().accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.exp(arg.getValue()));
        } else {
            return new Exp(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Log n) throws IllegalExpressionException, DivisionByZeroException{
        SymbolicExpression arg = n.arg().accept(this);
        if (arg.isConstant()) {
            if (arg.getValue()<=0){
                throw new IllegalExpressionException("The Logarithm of a number blow or equal to zero is undefined");
            }
            return new Constant(Math.log(arg.getValue()));
        } else {
            return new Log(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Multiplication n) throws IllegalExpressionException, DivisionByZeroException{
        SymbolicExpression leftFactor = n.lhs().accept(this);
        SymbolicExpression rightFactor = n.rhs().accept(this);
        if(leftFactor.isConstant() && rightFactor.isConstant()) {
            return new Constant(leftFactor.getValue() * rightFactor.getValue());
        } else {
            return new Multiplication(leftFactor, rightFactor);
        }
    }

    @Override
    public SymbolicExpression visit(NamedConstant n) throws IllegalExpressionException, DivisionByZeroException{
        return new Constant(n.getValue());
    }

    @Override
    public SymbolicExpression visit(Negation n) throws IllegalExpressionException, DivisionByZeroException{
        SymbolicExpression arg = n.arg().accept(this);
        if(arg.isConstant()) {
            return new Constant(-arg.getValue());
        } else if(arg instanceof Negation) {
            return ((Negation) arg).arg();
        } else {
            return new Negation(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Quit n) throws IllegalExpressionException, DivisionByZeroException{
        throw new RuntimeException("Commands may not be evaluated.");
    }

    @Override
    public SymbolicExpression visit(Sin n) throws IllegalExpressionException, DivisionByZeroException{
        SymbolicExpression arg = n.arg().accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.sin(arg.getValue()));
        } else {
            return new Sin(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Subtraction n) throws IllegalExpressionException, DivisionByZeroException{
        SymbolicExpression leftTerm = n.lhs().accept(this);
        SymbolicExpression rightTerm = n.rhs().accept(this);
        if(leftTerm.isConstant() && rightTerm.isConstant()) {
            return new Constant(leftTerm.getValue() - rightTerm.getValue());
        } else {
            return new Subtraction(leftTerm, rightTerm);
        }
    }

    @Override
    public SymbolicExpression visit(Variable n) throws IllegalExpressionException, DivisionByZeroException{
        SymbolicExpression value = env.get(n);
        return value == null ? n : value;
    }

    @Override
    public SymbolicExpression visit(Vars n) throws IllegalExpressionException, DivisionByZeroException{
        throw new RuntimeException("Commands may not be evaluated.");
    }

	@Override
	public SymbolicExpression visit(Clear n) throws IllegalExpressionException, DivisionByZeroException{
		throw new RuntimeException("Commands may not be evaluated.");
	}
}