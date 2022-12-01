package org.ioopm.calculator.parser;

import org.ioopm.calculator.Constants;
import org.ioopm.calculator.ast.*;

import java.io.StreamTokenizer;
import java.io.StringReader;
import java.io.IOException;
import java.util.LinkedList;

import java.util.*;

/**
 * Represents the parsing of strings into valid expressions defined in the AST.
 */
public class CalculatorParser {
    private StreamTokenizer st;
    private static char ASSIGNMENT = '=';
    private static char SUBTRACTION = '-';
    private static char ADDITION = '+';
    private static char DIVISION = '/';
    private static char MULTIPLY = '*';
    private static char NEGATION = '-';
    private static char EQUAL = '=';
    private static String NEG = "Neg";
    private static String SIN = "Sin";
    private static String COS = "Cos";
    private static String LOG = "Log";
    private static String EXP = "Exp";
    private EnvironmentStack env;
    private boolean isFunction;

    // unallowerdVars is used to check if variabel name that we
    // want to assign new meaning to is a valid name eg 3 = Quit
    // or 10 + x = L is not allowed
    private final ArrayList<String> unallowedVars = new ArrayList<String>(Arrays.asList("Quit",
            "Vars",
            "Clear",
            "Sin",
            "Cos",
            "Exp",
            "Log",
            "Neg",
            "if",
            "else",
            "function",
            "end"));

    /**
     * Used to parse the inputted string by the Calculator program
     * 
     * @param inputString the string used to parse
     * @param vars        the Environment in which the variables exist
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    public SymbolicExpression parse(String inputString, EnvironmentStack environmentStack)
            throws IOException, IllegalExpressionException, SyntaxErrorException {
        env = environmentStack;
        this.isFunction = false;
        this.st = new StreamTokenizer(new StringReader(inputString)); // reads from inputString via stringreader.
        this.st.ordinaryChar('-');
        this.st.ordinaryChar('/');
        this.st.eolIsSignificant(true);
        SymbolicExpression result = statement(); // calls to statement
        return result; // the final result
    }

    public boolean justParsedFunction() {
        return isFunction;
    }

    /**
     * Checks wether the token read is a command or an assignment
     * 
     * @return a SymbolicExpression to be evaluated
     * @throws IOException          by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a
     *                              valid expression
     */
    private SymbolicExpression statement() throws IOException, IllegalExpressionException, SyntaxErrorException {
        SymbolicExpression result;
        this.st.nextToken(); // kollar på nästa token som ligger på strömmen
        if (this.st.ttype == StreamTokenizer.TT_EOF) {
            throw new SyntaxErrorException("Error: Expected an expression");
        }

        if (this.st.ttype == StreamTokenizer.TT_WORD) { // vilken typ det senaste tecken vi läste in hade.
            if (this.st.sval.equals("Quit") || this.st.sval.equals("Vars") || this.st.sval.equals("Clear")
                    || this.st.sval.equals("end")) { // sval = string Variable
                result = command();
            } else if (this.st.sval.equals("function")) {
                result = function();
            } else {
                result = assignment(); // går vidare med uttrycket.
            }
        } else {
            result = assignment(); // om inte == word, gå till assignment ändå (kan vara tt_number)
        }

        if (this.st.nextToken() != StreamTokenizer.TT_EOF) { // token should be an end of stream token if we are done
            if (this.st.ttype == StreamTokenizer.TT_WORD) {
                throw new SyntaxErrorException("Error: Unexpected '" + this.st.sval + "'");
            } else {
                throw new SyntaxErrorException("Error: Unexpected '" + String.valueOf((char) this.st.ttype) + "'");
            }
        }
        return result;
    }

    private SymbolicExpression function() throws IOException, SyntaxErrorException {
        this.st.nextToken();
        if (this.st.ttype != StreamTokenizer.TT_WORD) {
            throw new SyntaxErrorException("Error: function name not a word!");
        }
        String name = this.st.sval;
        this.st.nextToken();
        if (this.st.ttype != '(') {
            throw new SyntaxErrorException("Error: expected a '(' after function name!");
        }
        LinkedList<Variable> arguments = new LinkedList<>();
        do {
            this.st.nextToken();
            if (this.st.ttype != StreamTokenizer.TT_WORD || this.unallowedVars.contains(this.st.sval)
                    || Constants.namedConstants.containsKey(this.st.sval)) {
                throw new SyntaxErrorException("Error: The function parameter " + this.st.sval + " isn't allowed!");
            }
            arguments.add(new Variable(this.st.sval));
            this.st.nextToken();
        } while (this.st.ttype == ',');
        if (this.st.ttype != ')') {
            throw new SyntaxErrorException("Error: expected a ')' after parameters!");
        }
        this.isFunction = true;
        return new FunctionDeclaration(name, arguments);
    }

    /**
     * Checks what kind of command that should be returned
     * 
     * @return an instance of Quit, Clear or Vars depending on the token parsed
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression command() throws IOException {
        if (this.st.sval.equals("Quit")) {
            return Quit.instance();
        } else if (this.st.sval.equals("Clear")) {
            return Clear.instance();
        } else if (this.st.sval.equals("Vars")) {
            return Vars.instance();
        } else {
            return End.instance();
        }
    }

    /**
     * Checks wether the token read is an assignment between 2 expression and
     * descend into the right hand side of '='
     * 
     * @return a SymbolicExpression to be evaluated
     * @throws IOException          by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a
     *                              valid expression,
     *                              the variable on rhs of '=' is a number or
     *                              invalid variable
     */
    private SymbolicExpression assignment() throws IOException, IllegalExpressionException, SyntaxErrorException {
        SymbolicExpression result = expression();
        this.st.nextToken();
        while (this.st.ttype == ASSIGNMENT) {
            this.st.nextToken();
            if (this.st.ttype == StreamTokenizer.TT_NUMBER) {
                throw new SyntaxErrorException("Error: Numbers cannot be used as a variable name");
            } else if (this.st.ttype != StreamTokenizer.TT_WORD) {
                throw new SyntaxErrorException("Error: Not a valid assignment of a variable"); // this handles faulty
                                                                                               // inputs after the equal
                                                                                               // sign eg. 1 = (x etc
            } else {
                if (this.st.sval.equals("ans")) {
                    throw new SyntaxErrorException("Error: ans cannot be redefined");
                }
                SymbolicExpression key = identifier();
                result = new Assignment(result, key);
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Check if valid identifier for variable and return that if so
     * 
     * @return a SymbolicExpression that is either a named constant or a new
     *         variable
     * @throws IOException                by nextToken() if it reads invalid input
     * @throws IllegalExpressionException if you try to redefine a string that isn't
     *                                    allowed
     */
    private SymbolicExpression identifier() throws IOException, IllegalExpressionException, SyntaxErrorException {
        SymbolicExpression result;

        if (this.unallowedVars.contains(this.st.sval)) {
            throw new IllegalExpressionException("Error: cannot redefine " + this.st.sval);
        }

        if (Constants.namedConstants.containsKey(this.st.sval)) {
            result = new NamedConstant(st.sval, Constants.namedConstants.get(st.sval));
        } else {
            String name = this.st.sval;
            if (this.st.nextToken() == '(') {
                LinkedList<Atom> arguments = new LinkedList<>();
                do {
                    this.st.nextToken();
                    if ((this.st.ttype != StreamTokenizer.TT_WORD && this.st.ttype != StreamTokenizer.TT_NUMBER)
                            || this.unallowedVars.contains(this.st.sval)) {
                        throw new SyntaxErrorException(
                                "Error: The function parameter " + this.st.sval + " isn't allowed!");
                    }
                    if (this.st.ttype == StreamTokenizer.TT_WORD) {
                        if (Constants.namedConstants.containsKey(this.st.sval)) {
                            arguments.add(new NamedConstant(st.sval, Constants.namedConstants.get(st.sval)));
                        } else {
                            arguments.add(new Variable(this.st.sval));
                        }
                    } else {
                        arguments.add(new Constant(this.st.nval));
                    }
                    this.st.nextToken();
                } while (this.st.ttype == ',');
                if (env.getFunction(name) != null) {
                    if (env.getFunction(name).getFDeclaration().getArguments().size() == arguments.size()) {
                        result = new FunctionCall(name, arguments);
                    } else {
                        throw new SyntaxErrorException(name + " called with wrong amount of arguments");
                    }
                } else {
                    throw new SyntaxErrorException(name + " is not a function");
                }
                if (this.st.ttype != ')') {
                    throw new SyntaxErrorException("expected ')'");
                }
            } else {
                this.st.pushBack();
                result = new Variable(name);
            }
        }
        return result;
    }

    private SymbolicExpression logicOperator(SymbolicExpression id1, SymbolicExpression id2, String op)
            throws SyntaxErrorException {
        SymbolicExpression result = null;
        if (op.equals("<")) {
            result = new LessThan(id1, id2);
        } else if (op.equals(">")) {
            result = new GreaterThan(id1, id2);
        } else if (op.equals("==")) {
            result = new Equal(id1, id2);
        } else if (op.equals(">=")) {
            result = new GreaterThanEqual(id1, id2);
        } else if (op.equals("<=")) {
            result = new LessThanEqual(id1, id2);
        } else {
            throw new SyntaxErrorException("Undefined logic operator");
        }
        return result;
    }

    /**
     * Checks wether the token read is an addition or subtraction
     * and then continue on with the right hand side of operator
     * 
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression expression() throws IOException, IllegalExpressionException, SyntaxErrorException {
        SymbolicExpression result = null;
        if (this.st.ttype == StreamTokenizer.TT_WORD && this.st.sval.equals("if")) {
            this.st.nextToken();
            SymbolicExpression variable1 = null;
            if (this.st.ttype == StreamTokenizer.TT_WORD && !(this.unallowedVars.contains(this.st.sval))
                    && !(Constants.namedConstants.containsKey(this.st.sval))) {
                variable1 = new Variable(this.st.sval);
            } else {
                throw new SyntaxErrorException("Error: Conditional identifier not a variable!");
            }
            this.st.nextToken();
            String op = Character.toString(this.st.ttype);
            this.st.nextToken();
            if (this.st.ttype == EQUAL) {
                op += "=";
                this.st.nextToken();
            }
            SymbolicExpression variable2 = null;
            if (this.st.ttype == StreamTokenizer.TT_WORD && !(this.unallowedVars.contains(this.st.sval))
                    && !(Constants.namedConstants.containsKey(this.st.sval))) {
                variable2 = new Variable(this.st.sval);
            } else {
                throw new SyntaxErrorException("Error: Conditional identifier not a variable!");
            }
            this.st.nextToken();
            SymbolicExpression scope1 = null;
            if (this.st.ttype == '{') {
                this.st.nextToken();
                scope1 = scope();
                /// This captures unbalanced scope parentheses!
                if (this.st.nextToken() != '}') {
                    throw new SyntaxErrorException("expected '}'");
                }
            } else {
                throw new SyntaxErrorException("missing scope");
            }
            this.st.nextToken();
            if (!(this.st.ttype == StreamTokenizer.TT_WORD && this.st.sval.equals("else"))) {
                throw new SyntaxErrorException("Error: Missing else-statement!");
            }
            this.st.nextToken();
            SymbolicExpression scope2 = null;
            if (this.st.ttype == '{') {
                this.st.nextToken();
                scope2 = scope();
                /// This captures unbalanced scope parentheses!
                if (this.st.nextToken() != '}') {
                    throw new SyntaxErrorException("expected '}'");
                }
            } else {
                throw new SyntaxErrorException("missing scope");
            }
            SymbolicExpression lOp = logicOperator(variable1, variable2, op);
            result = new Conditional(lOp, scope1, scope2);

        } else {
            result = term();
            this.st.nextToken();
            while (this.st.ttype == ADDITION || this.st.ttype == SUBTRACTION) {
                int operation = st.ttype;
                this.st.nextToken();
                if (operation == ADDITION) {
                    result = new Addition(result, term());
                } else {
                    result = new Subtraction(result, term());
                }
                this.st.nextToken();
            }
            this.st.pushBack();
        }
        return result;
    }

    /**
     * Checks wether the token read is an Multiplication or
     * Division and then continue on with the right hand side of
     * operator
     * 
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression term() throws IOException, IllegalExpressionException, SyntaxErrorException {
        SymbolicExpression result = primary();
        this.st.nextToken();
        while (this.st.ttype == MULTIPLY || this.st.ttype == DIVISION) {
            int operation = st.ttype;
            this.st.nextToken();

            if (operation == MULTIPLY) {
                result = new Multiplication(result, primary());
            } else {
                result = new Division(result, primary());
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Checks wether the token read is a parantheses and then
     * continue on with the expression inside of it or if the
     * operation is an unary operation and then continue on with
     * the right hand side of that operator else if it's a
     * number/identifier
     * 
     * @return a SymbolicExpression to be evaluated
     * @throws IOException          by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a
     *                              valid expression,
     *                              missing right parantheses
     */
    private SymbolicExpression primary() throws IOException, IllegalExpressionException, SyntaxErrorException {
        SymbolicExpression result;
        if (this.st.ttype == '(') {
            this.st.nextToken();
            result = assignment();
            /// This captures unbalanced parentheses!
            if (this.st.nextToken() != ')') {
                throw new SyntaxErrorException("expected ')'");
            }
        } else if (this.st.ttype == '{') {
            this.st.nextToken();
            result = scope();
            /// This captures unbalanced scope parentheses!
            if (this.st.nextToken() != '}') {
                throw new SyntaxErrorException("expected '}'");
            }
        } else if (this.st.ttype == NEGATION) {
            result = unary();
        } else if (this.st.ttype == StreamTokenizer.TT_WORD) {
            if (st.sval.equals(SIN) ||
                    st.sval.equals(COS) ||
                    st.sval.equals(EXP) ||
                    st.sval.equals(NEG) ||
                    st.sval.equals(LOG)) {

                result = unary();
            } else {
                result = identifier();
            }
        } else {
            this.st.pushBack();
            result = number();
        }
        return result;
    }

    /**
     * Checks what type of Unary operation the token read is and
     * then continues with the expression that the operator holds
     * 
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression unary() throws IOException, IllegalExpressionException, SyntaxErrorException {
        SymbolicExpression result;
        int operationNeg = st.ttype;
        String operation = st.sval;
        this.st.nextToken();
        if (operationNeg == NEGATION || operation.equals(NEG)) {
            result = new Negation(primary());
        } else if (operation.equals(SIN)) {
            result = new Sin(primary());
        } else if (operation.equals(COS)) {
            result = new Cos(primary());
        } else if (operation.equals(LOG)) {
            result = new Log(primary());
        } else {
            result = new Exp(primary());
        }
        return result;
    }

    private SymbolicExpression scope() throws IOException, IllegalExpressionException, SyntaxErrorException {
        return new Scope(assignment());
    }

    /**
     * Checks if the token read is a number - should always be a number in this
     * method
     * 
     * @return a SymbolicExpression to be evaluated
     * @throws IOException          by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a
     *                              valid expression,
     *                              expected a number which is not present
     */
    private SymbolicExpression number() throws IOException, SyntaxErrorException {
        this.st.nextToken();
        if (this.st.ttype == StreamTokenizer.TT_NUMBER) {
            return new Constant(this.st.nval);
        } else {
            throw new SyntaxErrorException("Error: Expected number");
        }
    }
}
