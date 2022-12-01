import static org.junit.jupiter.api.Assertions.*;

import java.io.IOException;
import java.util.LinkedList;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import org.ioopm.calculator.Constants;
import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

public class ParserTests {
    @BeforeAll
    static void initAll() {
    }

    @BeforeEach
    void init() {
    }

    // ------------------ "Unit tests" -----------------------

    @Test
    void testNumber() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression c = new Constant(7);
        SymbolicExpression p1 = cp.parse("7", env);
        SymbolicExpression p2 = cp.parse(c + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("3", env);
        assertNotEquals(p5, c);

        assertEquals(c, p1);
        assertEquals(c, p2);
        assertEquals(p2, p3);
    }

    @Test
    void testNotANumber() throws IOException, IllegalExpressionException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();

        try {
            cp.parse("/", env);
        } catch (SyntaxErrorException e) {
            assertTrue(true);
            return;
        }
        assertTrue(false);
    }

    @Test
    void testNegation() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression c = new Negation(new Constant(7));
        SymbolicExpression p1 = cp.parse("-7", env);
        SymbolicExpression p2 = cp.parse(c + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);
        SymbolicExpression p4 = cp.parse("Neg(7)", env);

        SymbolicExpression p5 = cp.parse("-9", env);
        assertNotEquals(p5, c);

        assertEquals(c, p1);
        assertEquals(c, p2);
        assertEquals(p2, p3);
        assertEquals(c, p4);
    }

    @Test
    void testSin() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression c = new Sin(new Constant(7));
        SymbolicExpression p1 = cp.parse("Sin 7", env);
        SymbolicExpression p2 = cp.parse(c + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);
        SymbolicExpression p4 = cp.parse("Sin(7)", env);

        SymbolicExpression p5 = cp.parse("Sin(19)", env);
        assertNotEquals(p5, c);

        assertEquals(c, p1);
        assertEquals(c, p2);
        assertEquals(p2, p3);
        assertEquals(c, p4);
    }

    @Test
    void testCos() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression c = new Cos(new Constant(7));
        SymbolicExpression p1 = cp.parse("Cos(7)", env);
        SymbolicExpression p2 = cp.parse(c + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);
        SymbolicExpression p4 = cp.parse("Cos 7", env);

        SymbolicExpression p5 = cp.parse("Cos(2)", env);
        assertNotEquals(p5, c);

        assertEquals(c, p1);
        assertEquals(c, p2);
        assertEquals(p2, p3);
        assertEquals(c, p4);
    }

    @Test
    void testExp() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression c = new Exp(new Constant(7));
        SymbolicExpression p1 = cp.parse("Exp 7", env);
        SymbolicExpression p2 = cp.parse(c + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);
        SymbolicExpression p4 = cp.parse("Exp(7)", env);

        SymbolicExpression p5 = cp.parse("Exp(4)", env);
        assertNotEquals(p5, c);

        assertEquals(c, p1);
        assertEquals(c, p2);
        assertEquals(p2, p3);
        assertEquals(c, p4);
    }

    @Test
    void testLog() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression c = new Log(new Constant(7));
        SymbolicExpression p1 = cp.parse("Log 7", env);
        SymbolicExpression p2 = cp.parse(c + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);
        SymbolicExpression p4 = cp.parse("Log(7)", env);

        SymbolicExpression p5 = cp.parse("Log(3)", env);
        assertNotEquals(p5, c);

        assertEquals(c, p1);
        assertEquals(c, p2);
        assertEquals(p2, p3);
        assertEquals(c, p4);
    }

    @Test
    void testVar() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression v = new Variable("f");
        SymbolicExpression p1 = cp.parse("f", env);
        SymbolicExpression p2 = cp.parse(v + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("x", env);
        assertNotEquals(p5, v);

        assertEquals(v, p1);
        assertEquals(v, p2);
        assertEquals(p2, p3);
    }

    @Test
    void testParentheses() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        Constant c = new Constant(5);
        SymbolicExpression p1 = cp.parse("(5)", env);
        SymbolicExpression p2 = cp.parse(c + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);
        SymbolicExpression p4 = cp.parse("5", env);

        assertEquals(c, p1);
        assertEquals(c, p2);
        assertEquals(p2, p3);
        assertEquals(c, p4);
    }

    @Test
    void testAdd() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression a = new Addition(new Constant(3), new Constant(5));

        SymbolicExpression p1 = cp.parse("3 + 5", env);
        SymbolicExpression p2 = cp.parse(a + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("3 + 1", env);
        assertNotEquals(p5, a);

        assertEquals(a, p1);
        assertEquals(a, p2);
        assertEquals(p2, p3);
    }

    @Test
    void testSub() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression a = new Subtraction(new Constant(8), new Constant(3));

        SymbolicExpression p1 = cp.parse("8 - 3", env);
        SymbolicExpression p2 = cp.parse(a + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("3 - 1", env);
        assertNotEquals(p5, a);

        assertEquals(a, p1);
        assertEquals(a, p2);
        assertEquals(p2, p3);
    }

    @Test
    void testDiv() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression a = new Division(new Constant(3), new Constant(6));

        SymbolicExpression p1 = cp.parse("3 / 6", env);
        SymbolicExpression p2 = cp.parse(a + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("3 / 4", env);
        assertNotEquals(p5, a);

        assertEquals(a, p1);
        assertEquals(a, p2);
        assertEquals(p2, p3);
    }

    @Test
    void testMul() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression a = new Multiplication(new Constant(3), new Constant(4));

        SymbolicExpression p1 = cp.parse("3 * 4", env);
        SymbolicExpression p2 = cp.parse(a + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("3 * 2", env);
        assertNotEquals(p5, a);

        assertEquals(a, p1);
        assertEquals(a, p2);
        assertEquals(p2, p3);
    }

    @Test
    void testCommand() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression p1 = cp.parse("Quit", env);

        SymbolicExpression p5 = cp.parse("Quot", env);
        assertNotEquals(p5, Quit.instance());

        assertEquals(Quit.instance(), p1);
    }

    @Test
    void testNamedConstant() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression p1 = cp.parse("pi", env);

        SymbolicExpression p5 = cp.parse("po", env);
        assertFalse(p5 instanceof NamedConstant);

        assertTrue(p1 instanceof NamedConstant);
    }

    @Test
    void testScope() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression c = new Scope(new Constant(7));
        SymbolicExpression p1 = cp.parse("{7}", env);
        SymbolicExpression p2 = cp.parse(c + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("(7)", env);
        assertNotEquals(p5, c);

        assertEquals(c, p1);
        assertEquals(c, p2);
        assertEquals(p2, p3);
    }

    @Test
    void testConditional() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression c = new Conditional(
                new LessThanEqual(
                        new Variable("x"),
                        new Variable("y")),
                new Scope(new Constant(5)),
                new Scope(new Constant(6)));
        SymbolicExpression p1 = cp.parse("if x <= y {5} else {6}", env);
        SymbolicExpression p2 = cp.parse(c + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("if x <= y {6} else {5}", env);
        assertNotEquals(p5, c);

        assertEquals(c, p1);
        assertEquals(c, p2);
        assertEquals(p2, p3);
    }

    @Test
    void testFunctionDeclaration() throws IOException, IllegalExpressionException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        LinkedList<Variable> arguments = new LinkedList<>();
        arguments.add(new Variable("a"));
        arguments.add(new Variable("b"));
        arguments.add(new Variable("c"));
        arguments.add(new Variable("d"));
        SymbolicExpression c = new FunctionDeclaration("Börje", arguments);
        SymbolicExpression p1 = cp.parse("function Börje(a, b, c, d)", env);

        SymbolicExpression p5 = cp.parse("function Börje(b, a, c, d)", env);
        assertNotEquals(p5, c);

        assertEquals(c, p1);
    }

    // --------------- "Integration tests" -------------------
    @Test
    void testSinCos() throws IllegalExpressionException, IOException, SyntaxErrorException, DivisionByZeroException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression s = new Sin(new Cos(new Constant(3.1415)));

        SymbolicExpression p1 = cp.parse("Sin(Cos(3.1415))", env);
        SymbolicExpression p2 = cp.parse(s + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("Cos(Sin(3.1415))", env);
        assertNotEquals(p5, s);

        assertEquals(s, p1);
        assertEquals(s, p2);
        assertEquals(p2, p3);
    }

    @Test
    void testNegExpLog() throws IllegalExpressionException, IOException, SyntaxErrorException, DivisionByZeroException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression s = new Negation(new Exp(new Log(new Constant(3.1415))));

        SymbolicExpression p1 = cp.parse("Neg(Exp(Log(3.1415)))", env);
        SymbolicExpression p2 = cp.parse(s + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("Exp(Neg(Log(3)))", env);
        assertNotEquals(p5, s);

        assertEquals(s, p1);
        assertEquals(s, p2);
        assertEquals(p2, p3);
    }

    @Test
    void testAddDiv() throws DivisionByZeroException, IllegalExpressionException, IOException, SyntaxErrorException {
        SymbolicExpression s = new Addition(
                new Division(
                        new Constant(3),
                        new Constant(2)),
                new Division(
                        new Constant(1),
                        new Constant(2)));

        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression p1 = cp.parse("3/2+1/2", env);
        SymbolicExpression p2 = cp.parse(s + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("3/(2+1)/2", env);
        assertNotEquals(p5, s);

        assertEquals(s, p1);
        assertEquals(s, p2);
        assertEquals(p2, p3);

    }

    @Test
    void testSubMul() throws IllegalExpressionException, IOException, SyntaxErrorException {
        Subtraction s = new Subtraction(new Multiplication(new Constant(3), new Constant(8)),
                new Multiplication(new Constant(9), new Constant(2)));
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();

        SymbolicExpression p1 = cp.parse("3*8-9*2", env);
        SymbolicExpression p2 = cp.parse(s + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("9*2-3*8", env);

        assertEquals(s, p1);
        assertEquals(s, p2);
        assertEquals(p2, p3);
        assertNotEquals(s, p5);
    }

    @Test
    void testSubScoVarDivSin() throws IllegalExpressionException, IOException, SyntaxErrorException {
        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();
        SymbolicExpression s = new Subtraction(
                new Scope(
                        new Division(
                                new Constant(24),
                                new Sin(
                                        new Division(
                                                new NamedConstant("pi", Constants.namedConstants.get("pi")),
                                                new Constant(2))))),
                new Constant(2));

        SymbolicExpression p1 = cp.parse("{24/Sin(pi/2)}-2", env);
        SymbolicExpression p2 = cp.parse(s + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("{24/(Sin(pi/2)-2)}", env);

        assertEquals(s, p1);
        assertEquals(s, p2);
        assertEquals(p2, p3);
        assertNotEquals(s, p5);

    }

    @Test
    void testMulCosNegExpAddLog() throws IllegalExpressionException, IOException, SyntaxErrorException {
        Multiplication m = new Multiplication(
                new Cos(
                        new Negation(
                                new Constant(2))),
                new Addition(
                        new Exp(
                                new Constant(23)),
                        new Log(
                                new Constant(Constants.namedConstants.get("e") - 1))));

        CalculatorParser cp = new CalculatorParser();
        EnvironmentStack env = new EnvironmentStack();

        SymbolicExpression p1 = cp.parse("Cos(-2)*(Exp(23)+Log(1.718281828459045))", env);
        SymbolicExpression p2 = cp.parse(m + "", env);
        SymbolicExpression p3 = cp.parse(p2 + "", env);

        SymbolicExpression p5 = cp.parse("Cos(-2)*Exp(23)+Log(1.718281828459045)", env);

        assertEquals(m, p1);
        assertEquals(m, p2);
        assertEquals(p2, p3);
        assertNotEquals(m, p5);
    }

    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }
}