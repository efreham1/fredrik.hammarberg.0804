package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;
import java.io.IOException;
import java.util.Scanner;

/**
* Command line calculator application
*
* @author Johan Yrefors & Fredrik Hammarberg
*/
public class Calculator {
    public static void main(String[] args) {
        final CalculatorParser parser = new CalculatorParser();
        final EnvironmentStack vars = new EnvironmentStack();
        final EvaluationVisitor ev = new EvaluationVisitor();
        final NamedConstantChecker ncc = new NamedConstantChecker();
        final ReassignmentChecker rc = new ReassignmentChecker();
        Scanner sc = new Scanner(System.in);

        int count = 0; // number of expressions entered during a single session
        int successes = 0; // number of expressions successfully evaluated during a single session

        System.out.println("");
        System.out.println("Welcome to the bestest calculator! GLHF");
        
        while(true) {
            String input = sc.nextLine();
            try {
                SymbolicExpression e = parser.parse(input);
                if(e.isCommand()) {
                    if(e == Quit.instance()) {
                        break;
                    } else if (e == Clear.instance()) {
                        vars.root().clear();
                    } else if (e == Vars.instance()) {
                        if(vars.root().size() != 0) {
                            System.out.println("" + vars.root());
                        } else {
                            System.out.println("No variables stored");
                        }
                    }
                } else {
                    try {
                        try {
                            if(ncc.check(e) && rc.check(e)) {
                                String result = ev.evaluate(e,vars).toString();
                                System.out.println(result);
                                successes++;
                                try {
                                    Constants.namedConstants.put("Answer", Double.parseDouble(result));
                                }
                                catch(NumberFormatException exception) {
                                    successes--;
                                }
                            }
                        } catch (DivisionByZeroException exception) {
                            System.out.println("***"+ exception.getMessage() + "***");
                        }
                    } catch (NamedConstantAssignmentException exception) {
                        System.out.println("***"+ exception.getMessage() + "***");
                    } catch (ReassignmentException exception) {
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
            catch (RootEnvironmentException exception) {
                System.out.println("***"+ exception.getMessage() + "***");
            }
            count++;
        }

        sc.close();
        
        System.out.println("Thanks for using this calculator!\n" + "Number of entries done: " + count + "\nSuccessfully evaluated: " + successes);
    }
}