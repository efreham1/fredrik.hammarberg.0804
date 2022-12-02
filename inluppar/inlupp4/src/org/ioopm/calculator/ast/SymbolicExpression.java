package org.ioopm.calculator.ast;

import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.NonConstantVariableException;
import org.ioopm.calculator.Visitor;

/**
 * Root class of the abstract syntax tree for representing
 * mathematical expressions
 *
 * @author Johan Yrefors & Fredrik Hammarberg
 */
public abstract class SymbolicExpression {
    private String name;
    private String[] subExpressions;

    public SymbolicExpression(String name, Object... subExpressions) {
        this.name = name;
        this.subExpressions = new String[subExpressions.length];
        for (int i = 0; i < subExpressions.length; ++i) {
            this.subExpressions[i] = subExpressions[i].toString();
        }
    }

    /**
     * @return String representation of the expression
     */
    public String toString(String msg) {
        StringBuilder sb = new StringBuilder();
        sb.append(this.name);
        sb.append("(");
        for (int i = 1; i < this.subExpressions.length; ++i) {
            sb.append(this.subExpressions[i]);
            if (i + 1 < subExpressions.length) {
                sb.append(", ");
            }
        }
        sb.append(")");
        return sb.toString();
    }

    /**
     * @return true if the SymbolicExpression is constant, otherwise false
     */
    public boolean isConstant() {
        return false;
    }

    /**
     * @return The name of the Symbolic expression
     */
    public String getName() {
        throw new RuntimeException("getName() called on expression with no operator.");
    }

    /**
     * Get the priority of the operation (lowest (0) - highest (3))
     * 
     * @return an int representing the priority of the operation
     */
    public int getPriority() {
        return 3;
    }

    public double getValue() {
        throw new RuntimeException("getValue() called on non-constant expression.");
    }

    /**
     * Accepts a Visitor
     *
     * @param v The Visitor to be accepted
     * @return The Visitors return
     */
    public abstract SymbolicExpression accept(Visitor v)
            throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException,
            ReassignmentException, RootEnvironmentException, NonConstantVariableException;

    /**
     * @return true if the SymbolicExpression is a command, otherwise false
     */
    public boolean isCommand() {
        return false;
    }
}
