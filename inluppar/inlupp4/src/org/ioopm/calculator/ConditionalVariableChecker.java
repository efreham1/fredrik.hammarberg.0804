package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;

public class ConditionalVariableChecker implements Visitor {
  EnvironmentStack env;

  public boolean check(SymbolicExpression topLevel, EnvironmentStack env)
      throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
      ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    this.env = env;
    topLevel.accept(this);
    return true;
  }

  @Override
  public SymbolicExpression visit(Addition n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    n.lhs().accept(this);
    n.rhs().accept(this);
    return n;
  }

  @Override
  public SymbolicExpression visit(Assignment n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    n.lhs().accept(this);
    return n;
  }

  @Override
  public SymbolicExpression visit(Clear n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    return n;
  }

  @Override
  public SymbolicExpression visit(Constant n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    return n;
  }

  @Override
  public SymbolicExpression visit(Cos n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    n.arg().accept(this);
    return n;
  }

  @Override
  public SymbolicExpression visit(Division n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    n.lhs().accept(this);
    n.rhs().accept(this);
    return n;
  }

  @Override
  public SymbolicExpression visit(Exp n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    n.arg().accept(this);
    return n;
  }

  @Override
  public SymbolicExpression visit(Log n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    n.arg().accept(this);
    return n;
  }

  @Override
  public SymbolicExpression visit(Multiplication n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    n.lhs().accept(this);
    n.rhs().accept(this);
    return n;
  }

  @Override
  public SymbolicExpression visit(NamedConstant n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    return n;
  }

  @Override
  public SymbolicExpression visit(Negation n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    n.arg().accept(this);
    return n;
  }

  @Override
  public SymbolicExpression visit(Quit n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    return n;
  }

  @Override
  public SymbolicExpression visit(Sin n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    n.arg().accept(this);
    return n;
  }

  @Override
  public SymbolicExpression visit(Subtraction n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    n.lhs().accept(this);
    n.rhs().accept(this);
    return n;
  }

  @Override
  public SymbolicExpression visit(Variable n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    return n;
  }

  @Override
  public SymbolicExpression visit(Vars n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    return n;
  }

  @Override
  public SymbolicExpression visit(Scope n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    n.arg().accept(this);
    return n;
  }

  @Override
  public SymbolicExpression visit(Conditional n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    n.getConditionalOperator().accept(this);
    n.getIfScope().accept(this);
    n.getElseScope().accept(this);
    return n;
  }

  @Override
  public SymbolicExpression visit(Equal n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    SymbolicExpression lhs = env.getVariable((Variable) n.lhs());
    SymbolicExpression rhs = env.getVariable((Variable) n.rhs());
    if (lhs != null && rhs != null && lhs.isConstant() && rhs.isConstant()) {
      return n;
    }
    throw new NonConstantVariableException("Error: Variable in Conditional operator is non-constant");
  }

  @Override
  public SymbolicExpression visit(GreaterThan n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    SymbolicExpression lhs = env.getVariable((Variable)n.lhs());
    SymbolicExpression rhs = env.getVariable((Variable) n.rhs());
    if (lhs != null && rhs != null && lhs.isConstant() && rhs.isConstant()) {
      return n;
    }
    throw new NonConstantVariableException("Error: Variable in Conditional operator is non-constant");
  }

  @Override
  public SymbolicExpression visit(GreaterThanEqual n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    SymbolicExpression lhs = env.getVariable((Variable) n.lhs());
    SymbolicExpression rhs = env.getVariable((Variable) n.rhs());
    if (lhs != null && rhs != null && lhs.isConstant() && rhs.isConstant()) {
      return n;
    }
    throw new NonConstantVariableException("Error: Variable in Conditional operator is non-constant");

  }

  @Override
  public SymbolicExpression visit(LessThan n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    SymbolicExpression lhs = env.getVariable((Variable) n.lhs());
    SymbolicExpression rhs = env.getVariable((Variable) n.rhs());
    if (lhs != null && rhs != null && lhs.isConstant() && rhs.isConstant()) {
      return n;
    }
    throw new NonConstantVariableException("Error: Variable in Conditional operator is non-constant");
  }

  @Override
  public SymbolicExpression visit(LessThanEqual n) throws IllegalExpressionException, DivisionByZeroException,
      NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    SymbolicExpression lhs = env.getVariable((Variable) n.lhs());
    SymbolicExpression rhs = env.getVariable((Variable) n.rhs());
    if (lhs != null && rhs != null && lhs.isConstant() && rhs.isConstant()) {
      return n;
    }
    throw new NonConstantVariableException("Error: Variable in Conditional operator is non-constant");
  }

  @Override
  public SymbolicExpression visit(End n)
      throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
      ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    return n;
  }

  @Override
  public SymbolicExpression visit(FunctionCall n)
      throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
      ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    return n;
  }

  @Override
  public SymbolicExpression visit(FunctionDeclaration n)
      throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
      ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    return n;
  }

  @Override
  public SymbolicExpression visit(Sequence n)
      throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
      ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    return n;
  }
}