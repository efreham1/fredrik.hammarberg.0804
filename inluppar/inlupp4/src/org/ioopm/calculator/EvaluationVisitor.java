package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;

public class EvaluationVisitor implements Visitor {
    private EnvironmentStack env = null;

    public SymbolicExpression evaluate(SymbolicExpression topLevel, EnvironmentStack env)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        this.env = env;
        return topLevel.accept(this);
    }

    // This method gets called from Addition.accept(Visitor v) -- you should
    // be able to see from the eval() methods how these should behave (i.e.,
    // compare this method with your Addition::eval() and Symbolic.addition)
    public SymbolicExpression visit(Addition n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
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
    public SymbolicExpression visit(Assignment n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        SymbolicExpression left = n.lhs().accept(this);
        Variable v = (Variable) n.rhs();
        env.putVariable(v, left);
        return left;
    }

    @Override
    public SymbolicExpression visit(Constant n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        return n;
    }

    @Override
    public SymbolicExpression visit(Cos n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        SymbolicExpression arg = n.arg().accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.cos(arg.getValue()));
        } else {
            return new Cos(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Division n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        SymbolicExpression numerator = n.lhs().accept(this);
        SymbolicExpression denominator = n.rhs().accept(this);
        if (numerator.isConstant() && denominator.isConstant()) {
            if (Math.abs(denominator.getValue()) < 1e-15) {
                throw new DivisionByZeroException("Division by 0 is undefined");
            }
            return new Constant(numerator.getValue() / denominator.getValue());
        } else {
            return new Division(numerator, denominator);
        }
    }

    @Override
    public SymbolicExpression visit(Exp n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        SymbolicExpression arg = n.arg().accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.exp(arg.getValue()));
        } else {
            return new Exp(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Log n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        SymbolicExpression arg = n.arg().accept(this);
        if (arg.isConstant()) {
            if (arg.getValue() <= 0) {
                throw new IllegalExpressionException("The Logarithm of a number blow or equal to zero is undefined");
            }
            return new Constant(Math.log(arg.getValue()));
        } else {
            return new Log(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Multiplication n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        SymbolicExpression leftFactor = n.lhs().accept(this);
        SymbolicExpression rightFactor = n.rhs().accept(this);
        if (leftFactor.isConstant() && rightFactor.isConstant()) {
            return new Constant(leftFactor.getValue() * rightFactor.getValue());
        } else {
            return new Multiplication(leftFactor, rightFactor);
        }
    }

    @Override
    public SymbolicExpression visit(NamedConstant n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        return new Constant(n.getValue());
    }

    @Override
    public SymbolicExpression visit(Negation n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        SymbolicExpression arg = n.arg().accept(this);
        if (arg.isConstant()) {
            return new Constant(-arg.getValue());
        } else if (arg instanceof Negation) {
            return ((Negation) arg).arg();
        } else {
            return new Negation(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Quit n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        throw new RuntimeException("Commands may not be evaluated.");
    }

    @Override
    public SymbolicExpression visit(Sin n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        SymbolicExpression arg = n.arg().accept(this);
        if (arg.isConstant()) {
            return new Constant(Math.sin(arg.getValue()));
        } else {
            return new Sin(arg);
        }
    }

    @Override
    public SymbolicExpression visit(Subtraction n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        SymbolicExpression leftTerm = n.lhs().accept(this);
        SymbolicExpression rightTerm = n.rhs().accept(this);
        if (leftTerm.isConstant() && rightTerm.isConstant()) {
            return new Constant(leftTerm.getValue() - rightTerm.getValue());
        } else {
            return new Subtraction(leftTerm, rightTerm);
        }
    }

    @Override
    public SymbolicExpression visit(Variable n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        SymbolicExpression value = env.getVariable(n);
        return value == null ? n : value;
    }

    @Override
    public SymbolicExpression visit(Vars n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        throw new RuntimeException("Commands may not be evaluated.");
    }

    @Override
    public SymbolicExpression visit(Clear n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        throw new RuntimeException("Commands may not be evaluated.");
    }

    @Override
    public SymbolicExpression visit(Scope n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        env.pushEnvironment();
        SymbolicExpression result = n.arg().accept(this);
        env.popEnvironment();
        return result;
    }

    @Override
    public SymbolicExpression visit(Conditional n) throws IllegalExpressionException, DivisionByZeroException,
            NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException,
            NonConstantVariableException {
        if (n.getConditionalOperator().accept(this).getValue() == 1) {
            return n.getIfScope().accept(this);
        } else {
            return n.getElseScope().accept(this);
        }
    }

    @Override
    public SymbolicExpression visit(Equal n) throws IllegalExpressionException, DivisionByZeroException,
            NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException,
            NonConstantVariableException {
                SymbolicExpression lhs = n.lhs().accept(this);
                SymbolicExpression rhs = n.rhs().accept(this);
                if (!(lhs.isConstant() && rhs.isConstant())){
                    throw new IllegalExpressionException("Error: Identifiers in logic condition non-constant!");
                }
                if (lhs.getValue() == rhs.getValue()) {
                    return new Constant(1);
        } else {
            return new Constant(0);
        }
    }

    @Override
    public SymbolicExpression visit(GreaterThan n) throws IllegalExpressionException, DivisionByZeroException,
            NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException,
            NonConstantVariableException {
                SymbolicExpression lhs = n.lhs().accept(this);
                SymbolicExpression rhs = n.rhs().accept(this);
                if (!(lhs.isConstant() && rhs.isConstant())){
                    throw new IllegalExpressionException("Error: Identifiers in logic condition non-constant!");
                }
                if (lhs.getValue() > rhs.getValue()) {
                    return new Constant(1);
        } else {
            return new Constant(0);
        }
    }

    @Override
    public SymbolicExpression visit(GreaterThanEqual n) throws IllegalExpressionException, DivisionByZeroException,
            NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException,
            NonConstantVariableException {
                SymbolicExpression lhs = n.lhs().accept(this);
                SymbolicExpression rhs = n.rhs().accept(this);
                if (!(lhs.isConstant() && rhs.isConstant())){
                    throw new IllegalExpressionException("Error: Identifiers in logic condition non-constant!");
                }
                if (lhs.getValue() >= rhs.getValue()) {
                    return new Constant(1);
        } else {
            return new Constant(0);
        }
    }

    @Override
    public SymbolicExpression visit(LessThan n) throws IllegalExpressionException, DivisionByZeroException,
            NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException,
            NonConstantVariableException {
                SymbolicExpression lhs = n.lhs().accept(this);
                SymbolicExpression rhs = n.rhs().accept(this);
                if (!(lhs.isConstant() && rhs.isConstant())){
                    throw new IllegalExpressionException("Error: Identifiers in logic condition non-constant!");
                }
                if (lhs.getValue() < rhs.getValue()) {
                    return new Constant(1);
        } else {
            return new Constant(0);
        }
    }

    @Override
    public SymbolicExpression visit(LessThanEqual n) throws IllegalExpressionException, DivisionByZeroException,
            NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException,
            NonConstantVariableException {
        SymbolicExpression lhs = n.lhs().accept(this);
        SymbolicExpression rhs = n.rhs().accept(this);
        if (!(lhs.isConstant() && rhs.isConstant())){
            throw new IllegalExpressionException("Error: Identifiers in logic condition non-constant!");
        }
        if (lhs.getValue() <= rhs.getValue()) {
            return new Constant(1);
        } else {
            return new Constant(0);
        }
    }

    @Override
    public SymbolicExpression visit(End n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        throw new RuntimeException("Commands may not be evaluated.");
    }

    @Override
    public SymbolicExpression visit(FunctionCall n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        String functionName = n.getFunctionName();
        FunctionDeclaration functionDeclaration = env.getFunction(functionName).getFDeclaration();
        Sequence functionBody = env.getFunction(functionName).getFunctionBody();
        env.pushEnvironment();
        int i = 0;
        SymbolicExpression result = new Constant(0);
        for (Variable var : functionDeclaration.getArguments()){
            env.putVariable(var, n.getArguments().get(i++).accept(this));
        }
        for (SymbolicExpression step : functionBody.getFunctionSteps()){
            result = step.accept(this);
        }
        env.popEnvironment();
        return result;
    }

    @Override
    public SymbolicExpression visit(FunctionDeclaration n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public SymbolicExpression visit(Sequence n)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        // TODO Auto-generated method stub
        return null;
    }
}