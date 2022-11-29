package org.ioopm.calculator;
import org.ioopm.calculator.ast.*;

public interface Visitor {
    public SymbolicExpression visit(Addition n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Assignment n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Clear n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Constant n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Cos n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Division n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Exp n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Log n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Multiplication n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(NamedConstant n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Negation n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Quit n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Sin n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Subtraction n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Variable n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
    public SymbolicExpression visit(Vars n) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException;
}