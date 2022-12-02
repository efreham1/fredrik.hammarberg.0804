package org.ioopm.calculator;

import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;
import java.io.IOException;
import java.util.Scanner;

/**
 * Command line interpreted programming language application
 *
 * @author Johan Yrefors & Fredrik Hammarberg & Simon Eriksson
 */
public class Calculator {

    public static void main(String[] args) {
        final CalculatorParser parser = new CalculatorParser();
        final EnvironmentStack env = new EnvironmentStack();
        final EvaluationVisitor ev = new EvaluationVisitor();
        final NamedConstantChecker ncc = new NamedConstantChecker();
        final ReassignmentChecker rc = new ReassignmentChecker();
        final ConditionalVariableChecker cvc = new ConditionalVariableChecker();
        Scanner sc = new Scanner(System.in);

        int count = 0; // number of expressions entered during a single session
        int successes = 0; // number of expressions successfully evaluated during a single session
        boolean inFunction = false;
        String functionName = null;
        int functionRow = 1;
        System.out.println("");
        System.out.println("Welcome to the omegalulz interpreter! GLHF");

        while (true) {
            try {
                if (inFunction) {
                    System.out.print("r" + functionRow + "f>");
                    String input = sc.nextLine();
                    SymbolicExpression e = parser.parse(input, env);
                    if (parser.justParsedFunction()) {
                        System.out.println(
                                "***Error: function declaration inside of a function definition not allowed!***");
                    } else {
                        if (e.isCommand() && e != End.instance() && e != Quit.instance()) {
                            System.out.println("***Error: commands can not be used in function body!***");
                            functionRow--;
                        } else if (e == End.instance()) {
                            if (env.getFunction(functionName).getFunctionBody().isEmpty()) {
                                System.out.println("***Error: an empty function body is not allowed!***");
                                functionRow--;
                            } else {
                                inFunction = false;
                                functionRow = 0;
                            }

                        } else if (e == Quit.instance()) {
                            inFunction = false;
                            env.remove(functionName);
                            functionRow = 0;
                        } else {
                            env.getFunction(functionName).getFunctionBody().addStep(e);
                        }
                        functionRow++;
                    }

                } else {
                    System.out.print("?> ");
                    String input = sc.nextLine();
                    SymbolicExpression e = parser.parse(input, env);
                    if (e.isCommand()) {
                        count++;
                        if (e == Quit.instance()) {
                            break;
                        } else if (e == Clear.instance()) {
                            env.clear();
                        } else if (e == Vars.instance()) {
                            if (env.size() != 0) {
                                System.out.println("" + env);
                            } else {
                                System.out.println("No variables or functions stored");
                            }
                        } else if (e == End.instance()) {
                            System.out.println("***Error: end used outside of a function definition!***");
                        }
                    } else {
                        count++;
                        if (ncc.check(e) && rc.check(e) && cvc.check(e, env)) {
                            if (parser.justParsedFunction()) {
                                inFunction = true;
                                functionName = e.getName();
                                env.putFunction(e.getName(),
                                        new Function((FunctionDeclaration) e, new Sequence()));

                            } else {
                                String result = ev.evaluate(e, env).toString();
                                System.out.println(result);
                                successes++;
                                Constants.namedConstants.put("Answer", Double.parseDouble(result));
                            }
                        }
                    }
                }
            } catch (NumberFormatException exception) {
                successes--;

            } catch (DivisionByZeroException exception) {
                System.out.println("***" + exception.getMessage() + "***");

            } catch (NamedConstantAssignmentException exception) {
                System.out.println("***" + exception.getMessage() + "***");

            } catch (ReassignmentException exception) {
                System.out.println("***" + exception.getMessage() + "***");

            } catch (NonConstantVariableException exception) {
                System.out.println("***" + exception.getMessage() + "***");

            } catch (IOException exception) {
                System.out.println("***" + exception.getMessage() + "***");

            } catch (IllegalExpressionException exception) {
                System.out.println("***" + exception.getMessage() + "***");

            } catch (SyntaxErrorException exception) {
                System.out.println("***" + exception.getMessage() + "***");

            } catch (RootEnvironmentException exception) {
                System.out.println("***" + exception.getMessage() + "***");

            }
        }

        sc.close();

        System.out.println("Thanks for using this calculator!\n" + "Number of entries done: " + count
                + "\nSuccessfully evaluated: " + successes);
    }
}