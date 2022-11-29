package org.ioopm.calculator.ast;
import java.util.TreeSet;
import java.util.HashMap;

/**
 * Data structure in which to store variables for the AST
 */
public class Environment extends HashMap<Variable, SymbolicExpression> {

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Variables: \n");
        TreeSet<Variable> vars = new TreeSet<>(this.keySet());
        for (Variable v : vars) {
            sb.append(v);
            sb.append(" = ");
            sb.append(this.get(v));
            sb.append("\n");
        }
        sb.deleteCharAt(sb.length() - 1);
        return sb.toString();
    }
}
