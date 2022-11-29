package org.ioopm.calculator.ast;
import java.util.Stack;

/**
 * EnvironmentStack
 */
public class EnvironmentStack extends Environment{
    private Stack<Environment> stack = new Stack<>();
    private Environment root = new Environment();

    public EnvironmentStack(){
        stack.push(root);
    }

    @Override
    public SymbolicExpression get(Object K){
        SymbolicExpression result = stack.peek().get(K);
        if (result == null && stack.size() > 1){
            Stack<Environment> reverseStack = new Stack<>();
            while (result == null && stack.size() > 1){
                reverseStack.push(stack.pop());
                result = stack.peek().get(K);
            }
            while (reverseStack.size() > 0) {
                stack.push(reverseStack.pop());
            }
        }
        return result;
    }

    @Override
    public SymbolicExpression put(Variable K, SymbolicExpression V){
        return stack.peek().put(K, V);
    }

    public void pushEnvironment(){
        stack.push(new Environment());
    }

    public void popEnvironment() throws RootEnvironmentException{
        if (stack.size() == 1) {
            throw new RootEnvironmentException("Error: Root environment removal not allowed!");
        } else {
            stack.pop();
        }
    }

    public Environment root(){
        return root;
    }
}