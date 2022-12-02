package org.ioopm.calculator.ast;

import java.util.TreeSet;
import java.util.HashMap;

/**
 * Data structure in which to store variables for the AST
 */
public class Environment {
    private HashMap<Variable, SymbolicExpression> Variables;
    private HashMap<String, Function> Functions;
    private boolean functionsAllowed;

    public Environment(boolean functionsAllowed) {
        Variables = new HashMap<>();
        this.functionsAllowed = functionsAllowed;
        if (this.functionsAllowed) {
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
        if (vars.size() == 0) {
            sb.append("No variables stored!\n");
        }
        if (functionsAllowed) {
            sb.append("Functions: \n");
            TreeSet<String> funcs = new TreeSet<>(Functions.keySet());
            for (String f : funcs) {
                sb.append(this.getFunction(f).getFDeclaration());
                sb.append("\n");
            }
            if (funcs.size() == 0) {
                sb.append("No functions stored!");
            }
            sb.deleteCharAt(sb.length() - 1);
        }
        return sb.toString();
    }

    public SymbolicExpression getVariable(Variable v) {
        return Variables.get(v);
    }

    public Function getFunction(String name) {
        if (!functionsAllowed) {
            throw new RuntimeException("getFunction called on a non-functional environment");
        }
        return Functions.get(name);
    }

    public SymbolicExpression putVariable(Variable v, SymbolicExpression se) {
        if (functionsAllowed && Functions.containsKey(v.toString())) {
            Functions.remove(v.toString());
        }
        return Variables.put(v, se);
    }

    public SymbolicExpression putFunction(String name, Function f) {
        if (!functionsAllowed) {
            throw new RuntimeException("putFunction called on a non-functional environment");
        }
        if (Variables.containsKey(new Variable(name))) {
            Variables.remove(new Variable(name));
        }
        return Functions.put(name, f);
    }

    public boolean contains(String name) {
        if (functionsAllowed) {
            return false;
        }
        return Functions.containsKey(name) || Variables.containsKey(new Variable(name));
    }

    public boolean contains(Variable v) {
        return Variables.containsKey(v) || Functions.containsKey(v.toString());
    }

    public int size() {
        int sum = Variables.size();
        if (functionsAllowed) {
            sum += Functions.size();
        }
        return sum;
    }

    public void clear() {
        Variables.clear();
        if (functionsAllowed) {
            Functions.clear();
        }
    }

    public void remove(String name) {
        if (functionsAllowed) {
            Functions.remove(name);
        } else {
            throw new RuntimeException("Tried to remove function from non-functional environment");
        }
    }

    public void remove(Variable v) {
        Variables.remove(v);
    }
}
