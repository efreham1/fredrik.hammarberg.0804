package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;
import java.io.IOException;
import java.util.Map;

/**
* Command line calculator application
*
* @author Johan Yrefors & Fredrik Hammarberg
*/
public class Calculator {
    public static void main(String[] args) {
        final CalculatorParser parser = new CalculatorParser();
        final Environment vars = new Environment();

        int count = 0; // number of expressions entered during a single session
        int successes = 0; // number of expressions successfully evaluated during a single session

        System.out.println("");
        System.out.println("Welcome to the bestest calculator! GLHF");
        
        while(true) {
            String input = System.console().readLine();
            try {
                SymbolicExpression e = parser.parse(input, vars);
                if(e.isCommand()) {
                    if(e == Quit.instance()) {
                        break;
                    } else if (e == Clear.instance()) {
                        vars.clear();
                    } else if (e == Vars.instance()) {
                        if(vars.size() != 0) {
                            for(Variable variable : vars.keySet()) {
                                System.out.println(variable.toString() + ": " + vars.get(variable).toString());
                            }
                        } else {
                            System.out.println("No variables stored");
                        }
                    }
                } else {
                    try {
                        String result = e.eval(vars).toString();
                        System.out.println(result);
                        successes++;
                        try {
                            Constants.namedConstants.put("Answer", Double.parseDouble(result));
                        }
                        catch(NumberFormatException exception) {
                            successes--;
                        }
                    } catch (DivisionByZeroException exception) {
                        System.out.println("***"+ exception.getMessage() + "***");
                    }
                }
            }
            catch (IOException exception) {
                System.out.println("***"+ exception.getMessage() + "***");
            }
            catch (IllegalExpressionException exception) {
                System.out.println("***" + exception.getMessage() + "***");
            }
            catch (SyntaxErrorException exception) {
                System.out.println("***"+ exception.getMessage() + "***");
            }
            count++;
        }

        System.out.println("Thanks for using this calculator!\n" + "Number of entries done: " + count + "\nSuccessfully evaluated: " + successes);
    }
}