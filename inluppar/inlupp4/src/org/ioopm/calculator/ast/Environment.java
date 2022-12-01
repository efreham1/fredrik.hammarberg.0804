package org.ioopm.calculator.ast;

import java.util.TreeSet;
import java.util.HashMap;

/**
 * Data structure in which to store variables for the AST
 */
public class Environment {
    private HashMap<Variable, SymbolicExpression> Variables;
    private HashMap<String, Function> Functions;
    private boolean hasFunctions;

    public Environment(boolean hasFunctions) {
        Variables = new HashMap<>();
        this.hasFunctions = hasFunctions;
        if (this.hasFunctions) {
            Functions = new HashMap<>();
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Variables: \n");
        TreeSet<Variable> vars = new TreeSet<>(Variables.keySet());
        for (Variable v : vars) {
            sb.append(v);
            sb.append(" = ");
            sb.append(this.getVariable(v));
            sb.append("\n");
        }
        if (hasFunctions) {
            sb.append("Functions: \n");
            TreeSet<String> funcs = new TreeSet<>(Functions.keySet());
            for (String f : funcs) {
                sb.append(this.getFunction(f).getFDeclaration());
                sb.append("\n");
            }
            sb.deleteCharAt(sb.length() - 1);
        }
        return sb.toString();
    }

    public SymbolicExpression getVariable(Variable v) {
        return Variables.get(v);
    }

    public Function getFunction(String name) {
        if (!hasFunctions){
            throw new RuntimeException("getFunction called on a non-functional environment");
        }
        return Functions.get(name);
    }

    public SymbolicExpression putVariable(Variable v, SymbolicExpression se) {
        if (hasFunctions && Functions.containsKey(v.toString())) {
            Functions.remove(v.toString());
        }
        return Variables.put(v, se);
    }

    public SymbolicExpression putFunction(String name, Function f) {
        if (!hasFunctions){
            throw new RuntimeException("putFunction called on a non-functional environment");
        }
        if (Variables.containsKey(new Variable(name))) {
            Variables.remove(new Variable(name));
        }
        return Functions.put(name, f);
    }

    public boolean contains(String name) {
        if (hasFunctions){
            return false;
        }
        return Functions.containsKey(name) || Variables.containsKey(new Variable(name));
    }

    public boolean contains(Variable v) {
        return Variables.containsKey(v) || Functions.containsKey(v.toString());
    }

    public int size() {
        int sum = Variables.size();
        if (hasFunctions){
            sum += Functions.size();
        }
        return sum;
    }

    public void clear() {
        Variables.clear();
        if (hasFunctions){
            Functions.clear();
        }
    }

    public void remove(String name) {
        if (hasFunctions){
            Functions.remove(name);
        } else {
            throw new RuntimeException("Tried to remove function from non-functional environment");
        }
    }

    public void remove(Variable v) {
        Variables.remove(v);
    }
}
