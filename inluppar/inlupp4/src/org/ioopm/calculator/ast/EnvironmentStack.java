package org.ioopm.calculator.ast;

import java.util.Stack;

/**
 * EnvironmentStack
 */
public class EnvironmentStack extends Environment {
    private Stack<Environment> stack = new Stack<>();

    public EnvironmentStack() {
        super(true);
        stack.push(this);
    }

    @Override
    public SymbolicExpression getVariable(Variable v) {
        if (stack.peek().equals(this)){
            return super.getVariable(v);
        }
        SymbolicExpression result = stack.peek().getVariable(v);
        if (result == null && stack.size() > 1) {
            Stack<Environment> reverseStack = new Stack<>();
            while (result == null && stack.size() > 1) {
                reverseStack.push(stack.pop());
                result = stack.peek().getVariable(v);
            }
            while (reverseStack.size() > 0) {
                stack.push(reverseStack.pop());
            }
        }
        return result;
    }


    @Override
    public SymbolicExpression putVariable(Variable v, SymbolicExpression se) {
        if (stack.peek().equals(this)){
            return super.putVariable(v, se);
        }
        if (this.contains(v.toString())){
            this.remove(v.toString());
        }
        return stack.peek().putVariable(v, se);
    }

    public void pushEnvironment() {
        stack.push(new Environment(false));
    }

    @Override
    public boolean contains(Variable v){
        return stack.peek().contains(v);
    }

    @Override
    public SymbolicExpression putFunction(String name, Function f) {
        if (stack.size() != 1){
            throw new RuntimeException("Functions can not be defined inside scopes");
        }
        return super.putFunction(name, f);
    }

    public void removeFunction(String name){
        super.remove(name);
    }

    public void popEnvironment() throws RootEnvironmentException {
        if (stack.size() == 1) {
            throw new RootEnvironmentException("Error: Root environment removal not allowed!");
        } else {
            stack.pop();
        }
    }
}