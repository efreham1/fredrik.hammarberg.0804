import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

import org.ioopm.calculator.ast.*;


public class AstUnitTests {
    @BeforeAll
    static void initAll() {
    }

    @BeforeEach
    void init() {
    }

    // Constant -------------------------------------

    @Test
    void testConstantValue() {
        Constant c = new Constant(42);
        assertEquals(42, c.getValue());
    }

    @Test
    void testConstantIsConstant() {
        Constant c = new Constant(42);
        assertTrue(c.isConstant());
    }

    @Test
    void testConstantPriority() {
        Constant c = new Constant(42);
        assertEquals(3, c.getPriority());
    }

    @Test
    void testConstantToString() {
        Constant c = new Constant(1);
        assertEquals("1", c.toString());
    }

    @Test
    void testConstantEquals() {
        Constant c1 = new Constant(1);
        Constant c2 = new Constant(1);
        assertTrue(c1.equals(c2));
        assertTrue(c2.equals(c1));
    }

    @Test
    void testConstantEqualsFail() {
        Constant c1 = new Constant(1);
        Constant c2 = new Constant(2);
        assertFalse(c1.equals(c2));
        assertFalse(c2.equals(c1));
    }

    @Test
    void testConstantEval() throws IllegalExpressionException {
        Constant c = new Constant(1);
        Environment vars = new Environment();
        assertEquals(new Constant(1), c.eval(vars));
    }

    // Variable and Assignment ----------------------------------

    @Test
    void testVariableToString() {
        Variable v = new Variable("x");
        assertEquals("x", v.toString());
    }

    @Test
    void testVariableEquals() {
        Variable v1 = new Variable("x");
        Variable v2 = new Variable("x");
        assertTrue(v1.equals(v2));
        assertTrue(v2.equals(v1));
    }

    @Test
    void testVariableEqualsFail() {
        Variable v1 = new Variable("x");
        Variable v2 = new Variable("y");
        assertFalse(v1.equals(v2));
        assertFalse(v2.equals(v1));
    }

    @Test
    void testVariableEval() throws IllegalExpressionException {
        Variable v = new Variable("x");
        Constant c = new Constant(1);
        Environment vars = new Environment();
        Assignment a1 = new Assignment(c,v);
        assertEquals(c, a1.eval(vars));
        assertEquals(c, v.eval(vars));
    }

    // Addition -----------------------------------------------------

    @Test
    void testAdditionPriority() {
        Addition a = new Addition(new Constant(1), new Constant(1));
        assertEquals(0, a.getPriority());
    }

    @Test
    void testAdditionGetName() {
        Addition a = new Addition(new Constant(1), new Constant(1));
        assertEquals("+", a.getName());
    }

    @Test
    void testAdditionEval() throws IllegalExpressionException {
        Addition a = new Addition(new Constant(1), new Constant(1));
        Environment vars = new Environment();
        assertEquals(new Constant(2), a.eval(vars));
    }

    // Subtraction -------------------------------------------------------

    @Test
    void testSubtractionPriority() {
        Subtraction s = new Subtraction(new Constant(1), new Constant(1));
        assertEquals(0, s.getPriority());
    }

    @Test
    void testSubtractionGetName() {
        Subtraction s = new Subtraction(new Constant(1), new Constant(1));
        assertEquals("-", s.getName());
    }

    @Test
    void testSubtractionEval() throws IllegalExpressionException{
        Subtraction s = new Subtraction(new Constant(1), new Constant(1));
        Environment vars = new Environment();
        assertEquals(new Constant(0), s.eval(vars));
    }

    // Multiplication ----------------------------------------------------------

    @Test
    void testMultiplicationPriority() {
        Multiplication m = new Multiplication(new Constant(1), new Constant(1));
        assertEquals(1, m.getPriority());
    }
    @Test
    void testMultiplicationGetName() {
        Multiplication m = new Multiplication(new Constant(1), new Constant(1));
        assertEquals("*", m.getName());
    }

    @Test
    void testMultiplicationEval() throws IllegalExpressionException{
        Multiplication m = new Multiplication(new Constant(2), new Constant(3));
        Environment vars = new Environment();
        assertEquals(new Constant(6), m.eval(vars));
    }

    // Division ---------------------------------------------------

    @Test
    void testDivisionPriority() {
        Division s = new Division(new Constant(1), new Constant(1));
        assertEquals(1, s.getPriority());
    }

    @Test
    void testDivisionGetName() {
        Division s = new Division(new Constant(1), new Constant(1));
        assertEquals("/", s.getName());
    }

    @Test
    void testDivisionEval() throws IllegalExpressionException{
        Division s = new Division(new Constant(5), new Constant(2));
        Environment vars = new Environment();
        assertEquals(new Constant(2.5), s.eval(vars));
    }

    // Sin -------------------------------------------------------

    @Test
    void testSinGetName() {
        Sin s = new Sin(new Constant(0));
        assertEquals("sin", s.getName());
    }

    @Test
    void testSinPriority() {
        Sin s = new Sin(new Constant(0));
        assertEquals(2, s.getPriority());
    }

    @Test
    void testSinEval() throws IllegalExpressionException{
        Sin s = new Sin(new Constant(0));
        Environment vars = new Environment();
        assertEquals(new Constant(0), s.eval(vars));
    }
    
    // Cos ---------------------------------------------

    @Test
    void testCosGetName() {
        Cos cos = new Cos(new Constant(0));
        assertEquals("cos", cos.getName());
    }

    @Test
    void testCosPriority() {
        Cos cos = new Cos(new Constant(0));
        assertEquals(2, cos.getPriority());
    }

    @Test
    void testCosEval() throws IllegalExpressionException{
        Cos cos = new Cos(new Constant(0));
        Environment vars = new Environment();
        assertEquals(new Constant(1), cos.eval(vars));
    }
    
    // Exp -----------------------------------------------

    @Test
    void testExpGetName() {
        Exp exp = new Exp(new Constant(0));
        assertEquals("exp", exp.getName());
    }

    @Test
    void testExpPriority() {
        Exp exp = new Exp(new Constant(0));
        assertEquals(2, exp.getPriority());
    }

    @Test
    void testExpEval() throws IllegalExpressionException{
        Exp exp = new Exp(new Constant(0));
        Environment vars = new Environment();
        assertEquals(new Constant(1), exp.eval(vars));
    }
    
    // Log --------------------------------------------------

    @Test
    void testLogGetName() {
        Log log = new Log(new Constant(0));
        assertEquals("log", log.getName());
    }

    @Test
    void testLogPriority() {
        Log log = new Log(new Constant(0));
        assertEquals(2, log.getPriority());
    }

    @Test
    void testLogEval() throws IllegalExpressionException{
        Log log = new Log(new Constant(1));
        Environment vars = new Environment();
        assertEquals(new Constant(0), log.eval(vars));
    }
    
    // Negation -------------------------------------------

    @Test
    void testNegationGetName() {
        Negation neg = new Negation(new Constant(1));
        assertEquals("-", neg.getName());
    }

    @Test
    void testNegationPriority() {
        Negation neg = new Negation(new Constant(1));
        assertEquals(2, neg.getPriority());
    }

    @Test
    void testNegationToString() {
        Negation neg1 = new Negation(new Constant(1));
        assertEquals("-1", neg1.toString());
        Negation neg2 = new Negation(new Subtraction(new Constant(2), new Constant(3)));
        assertEquals("-(2 - 3)", neg2.toString());
    }

    @Test
    void testNegationEval() throws IllegalExpressionException {
        Negation neg = new Negation(new Constant(1));
        Environment vars = new Environment();
        assertEquals(new Constant (-1), neg.eval(vars));
    }

    @Test
    void testDoubleNegation() throws IllegalExpressionException {
        Negation neg = new Negation(new Negation(new Constant(1)));
        Environment vars = new Environment();
        assertEquals(new Constant(1), neg.eval(vars));
    }
    
    // NamedConstant and Constants --------------------------------

    @Test
    void testNamedConstantValue() {
        assertEquals(Constants.namedConstants.get("pi"), Math.PI);
    }

    @Test
    void testNamedConstantObject() {
        NamedConstant c = new NamedConstant("a", 5);
        assertEquals(c.getValue(), 5);
        assertEquals(c.toString(), "a");
    }

    @Test
    void testNamedConstantReassignment() {
        NamedConstant nc = new NamedConstant("x", 4);
        Constant c = new Constant(1);
        Environment vars = new Environment();
        Assignment a1 = new Assignment(c, nc);
        try{
            assertEquals(c, a1.eval(vars));
            assertEquals(c, nc.eval(vars));
        }
        catch (IllegalExpressionException e) {
            assertTrue(true);
            return;
        }
        assertTrue(false);
    }

    // ---------------------------------------------------



    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }
}