import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import org.ioopm.calculator.Constants;
import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.EvaluationVisitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.NamedConstantChecker;
import org.ioopm.calculator.ReassignmentException;

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
    void testConstantEval() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException{
        Constant c = new Constant(1);
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assertEquals(new Constant(1), ev.evaluate(c, vars));
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
    void testVariableEval() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Variable v = new Variable("x");
        Constant c = new Constant(1);
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        Assignment a1 = new Assignment(c,v);
        assertEquals(c, ev.evaluate(a1,vars));
        assertEquals(c, ev.evaluate(v,vars));
    }

    @Test
    void testMultipleAssignments() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Variable v1 = new Variable("x");
        Variable v2 = new Variable("y");
        Variable v3 = new Variable("z");
        Constant c = new Constant(1);
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        Assignment a1 = new Assignment(new Assignment(new Assignment(c, v3), v2),v1);
        assertEquals(c, ev.evaluate(a1,vars));
        assertEquals(c, ev.evaluate(v1,vars));
        assertEquals(c, ev.evaluate(v2,vars));
        assertEquals(c, ev.evaluate(v3,vars));
    }

    @Test
    void testIllegalVariable() throws DivisionByZeroException, IllegalExpressionException, ReassignmentException {
        NamedConstantChecker ncc = new NamedConstantChecker();
        Constant c = new Constant(1);
        Assignment a1 = new Assignment(c, new Constant(5));
        Assignment a2 = new Assignment(c, new NamedConstant("pi", 8));
        try {
            ncc.check(a1);
        } catch (NamedConstantAssignmentException e) {
            assertTrue(true);
            try {
                ncc.check(a2);
            } catch (NamedConstantAssignmentException ee) {
                assertTrue(true);
                return;
            }
        }
        assertFalse(false);
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
    void testAdditionEval() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Addition a = new Addition(new Constant(1), new Constant(1));
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assertEquals(new Constant(2), ev.evaluate(a,vars));
    }

    @Test
    void testAdditionEquals() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Addition a = new Addition(new Constant(32), new Constant(55));
        Addition b = new Addition(new Constant(32), new Constant(55));
        assertTrue(a.equals(b));
        assertTrue(b.equals(a));
    }

    @Test
    void testAdditionEqualsFail() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Addition a = new Addition(new Constant(32), new Constant(55));
        Addition b = new Addition(new Constant(23), new Constant(55));
        assertFalse(a.equals(b));
        assertFalse(b.equals(a));
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
    void testSubtractionEval() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException{
        Subtraction s = new Subtraction(new Constant(1), new Constant(1));
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assertEquals(new Constant(0), ev.evaluate(s,vars));
    }

    @Test
    void testSubtractionEquals() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Subtraction a = new Subtraction(new Constant(32), new Constant(55));
        Subtraction b = new Subtraction(new Constant(32), new Constant(55));
        assertTrue(a.equals(b));
        assertTrue(b.equals(a));
    }

    @Test
    void testSubtractionEqualsFail() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Subtraction a = new Subtraction(new Constant(32), new Constant(55));
        Subtraction b = new Subtraction(new Constant(23), new Constant(55));
        assertFalse(a.equals(b));
        assertFalse(b.equals(a));
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
    void testMultiplicationEval() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException{
        Multiplication m = new Multiplication(new Constant(2), new Constant(3));
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assertEquals(new Constant(6), ev.evaluate(m,vars));
    }

    @Test
    void testMultiplicationEquals() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Multiplication a = new Multiplication(new Constant(32), new Constant(55));
        Multiplication b = new Multiplication(new Constant(32), new Constant(55));
        assertTrue(a.equals(b));
        assertTrue(b.equals(a));
    }

    @Test
    void testMultiplicationEqualsFail() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Multiplication a = new Multiplication(new Constant(32), new Constant(55));
        Multiplication b = new Multiplication(new Constant(23), new Constant(55));
        assertFalse(a.equals(b));
        assertFalse(b.equals(a));
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
    void testDivisionEval() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException{
        Division s = new Division(new Constant(5), new Constant(2));
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assertEquals(new Constant(2.5), ev.evaluate(s,vars));
    }

    @Test
    void testDivisionByZero() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException{
        Division s = new Division(new Constant(5), new Constant(0));
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        try {
            ev.evaluate(s,vars);
        }
        catch (DivisionByZeroException e) {
            assertTrue(true);
            return;
        }
        assertTrue(false);
    }

    @Test
    void testDivisionEquals() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Division a = new Division(new Constant(32), new Constant(55));
        Division b = new Division(new Constant(32), new Constant(55));
        assertTrue(a.equals(b));
        assertTrue(b.equals(a));
    }

    @Test
    void testDivisionEqualsFail() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Division a = new Division(new Constant(32), new Constant(55));
        Division b = new Division(new Constant(23), new Constant(55));
        assertFalse(a.equals(b));
        assertFalse(b.equals(a));
    }

    // Sin -------------------------------------------------------

    @Test
    void testSinGetName() {
        Sin s = new Sin(new Constant(0));
        assertEquals("Sin", s.getName());
    }

    @Test
    void testSinPriority() {
        Sin s = new Sin(new Constant(0));
        assertEquals(2, s.getPriority());
    }

    @Test
    void testSinEval() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException{
        Sin s = new Sin(new Constant(0));
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assertEquals(new Constant(0), ev.evaluate(s,vars));
    }

    @Test
    void testSinEquals() {
        Sin c1 = new Sin(new Constant(1));
        Sin c2 = new Sin(new Constant(1));
        assertTrue(c1.equals(c2));
        assertTrue(c2.equals(c1));
    }

    @Test
    void testSinEqualsFail() {
        Sin c1 = new Sin(new Constant(1));
        Sin c2 = new Sin(new Constant(2));
        assertFalse(c1.equals(c2));
        assertFalse(c2.equals(c1));
    }
    
    // Cos ---------------------------------------------

    @Test
    void testCosGetName() {
        Cos cos = new Cos(new Constant(0));
        assertEquals("Cos", cos.getName());
    }

    @Test
    void testCosPriority() {
        Cos cos = new Cos(new Constant(0));
        assertEquals(2, cos.getPriority());
    }

    @Test
    void testCosEval() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException{
        Cos cos = new Cos(new Constant(0));
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assertEquals(new Constant(1), ev.evaluate(cos,vars));
    }

    @Test
    void testCosEquals() {
        Cos c1 = new Cos(new Constant(1));
        Cos c2 = new Cos(new Constant(1));
        assertTrue(c1.equals(c2));
        assertTrue(c2.equals(c1));
    }

    @Test
    void testCosEqualsFail() {
        Cos c1 = new Cos(new Constant(1));
        Cos c2 = new Cos(new Constant(2));
        assertFalse(c1.equals(c2));
        assertFalse(c2.equals(c1));
    }
    
    // Exp -----------------------------------------------

    @Test
    void testExpGetName() {
        Exp exp = new Exp(new Constant(0));
        assertEquals("Exp", exp.getName());
    }

    @Test
    void testExpPriority() {
        Exp exp = new Exp(new Constant(0));
        assertEquals(2, exp.getPriority());
    }

    @Test
    void testExpEval() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException{
        Exp exp = new Exp(new Constant(0));
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assertEquals(new Constant(1), ev.evaluate(exp,vars));
    }

    @Test
    void testExpEquals() {
        Exp c1 = new Exp(new Constant(1));
        Exp c2 = new Exp(new Constant(1));
        assertTrue(c1.equals(c2));
        assertTrue(c2.equals(c1));
    }

    @Test
    void testExpEqualsFail() {
        Exp c1 = new Exp(new Constant(1));
        Exp c2 = new Exp(new Constant(2));
        assertFalse(c1.equals(c2));
        assertFalse(c2.equals(c1));
    }
    
    // Log --------------------------------------------------

    @Test
    void testLogGetName() {
        Log log = new Log(new Constant(0));
        assertEquals("Log", log.getName());
    }

    @Test
    void testLogPriority() {
        Log log = new Log(new Constant(0));
        assertEquals(2, log.getPriority());
    }

    @Test
    void testLogEval() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException{
        Log log = new Log(new Constant(1));
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assertEquals(new Constant(0), ev.evaluate(log,vars));
    }

    @Test
    void testLogInvalidArgument() throws DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
        Log log = new Log(new Constant(-1.2));
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        try {
            ev.evaluate(log,vars);
        }
        catch (IllegalExpressionException e) {
            assertTrue(true);
            return;
        }
        assertTrue(false);
    }

    @Test
    void testLogEquals() {
        Log c1 = new Log(new Constant(1));
        Log c2 = new Log(new Constant(1));
        assertTrue(c1.equals(c2));
        assertTrue(c2.equals(c1));
    }

    @Test
    void testLogEqualsFail() {
        Log c1 = new Log(new Constant(1));
        Log c2 = new Log(new Constant(2));
        assertFalse(c1.equals(c2));
        assertFalse(c2.equals(c1));
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
    void testNegationEval() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Negation neg = new Negation(new Constant(1));
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assertEquals(new Constant (-1), ev.evaluate(neg,vars));
    }

    @Test
    void testDoubleNegation() throws IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, DivisionByZeroException {
        Negation neg = new Negation(new Negation(new Constant(1)));
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        assertEquals(new Constant(1), ev.evaluate(neg,vars));
    }

    @Test
    void testNegationEquals() {
        Negation c1 = new Negation(new Constant(1));
        Negation c2 = new Negation(new Constant(1));
        assertTrue(c1.equals(c2));
        assertTrue(c2.equals(c1));
    }

    @Test
    void testNegationEqualsFail() {
        Negation c1 = new Negation(new Constant(1));
        Negation c2 = new Negation(new Constant(2));
        assertFalse(c1.equals(c2));
        assertFalse(c2.equals(c1));
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
    void testNamedConstantReassignment() throws DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException {
        NamedConstant nc = new NamedConstant("x", 4);
        Constant c = new Constant(1);
        Environment vars = new Environment();
        EvaluationVisitor ev = new EvaluationVisitor();
        Assignment a1 = new Assignment(c, nc);
        try{
            assertEquals(c, ev.evaluate(a1, vars));
            assertEquals(c, ev.evaluate(nc, vars));
        }
        catch (IllegalExpressionException e) {
            assertTrue(true);
            return;
        }
        assertTrue(false);
    }

    @Test
    void testNamedConstantEquals() {
        NamedConstant c1 = new NamedConstant("a", 5);
        NamedConstant c2 = new NamedConstant("a", 5);
        assertTrue(c1.equals(c2));
        assertTrue(c2.equals(c1));
    }

    @Test
    void testNamedConstantEqualsFail() {
        NamedConstant c1 = new NamedConstant("a", 5);
        NamedConstant c2 = new NamedConstant("a", 6);
        assertFalse(c1.equals(c2));
        assertFalse(c2.equals(c1));
        NamedConstant c3 = new NamedConstant("b", 5);
        assertFalse(c1.equals(c3));
        assertFalse(c3.equals(c1));
    }

    // ---------------------------------------------------



    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }
}