import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import org.ioopm.calculator.Constants;
import org.ioopm.calculator.ast.*;

public class AstIntegrationTests {
    @BeforeAll
    static void initAll() {
    }

    @BeforeEach
    void init() {
    }


    // ------------------ Unary integration tests -----------------------

    @Test
    void testSinCos() throws DivisionByZeroException, IllegalExpressionException {
        Environment vars = new Environment();
        Sin s = new Sin(new Cos(new Constant(3.1415)));
        Constant c = (Constant) s.eval(vars);
        assertEquals(-0.8414709824887332, c.getValue());
    }

    @Test
    void testNegExpLog() throws DivisionByZeroException, IllegalExpressionException {
        Environment vars = new Environment();
        Negation n = new Negation(new Exp(new Log(new Constant(3))));
        Constant c = (Constant) n.eval(vars);
        assertEquals(-3.0000000000000004, c.getValue());
    }

    @Test
    void testExpNegLog() throws DivisionByZeroException, IllegalExpressionException {
        Environment vars = new Environment();
        SymbolicExpression n = new Exp(new Negation(new Log(new Constant(3))));
        Constant c = (Constant) n.eval(vars);
        assertEquals(0.3333333333333333, c.getValue());
    }

    // ------------------ Binary integration tests ----------------------
    
    @Test
    void testAddDiv() throws DivisionByZeroException, IllegalExpressionException {
        Environment vars = new Environment();
        Addition a = new Addition(new Division(new Constant(3),new Constant(2)),new Division(new Constant(1),new Constant(2)));
        Constant c = (Constant) a.eval(vars);
        assertEquals(2.0, c.getValue());
    }

    @Test
    void testSubMul() throws DivisionByZeroException, IllegalExpressionException {
        Environment vars = new Environment();
        Subtraction s = new Subtraction(new Multiplication(new Constant(3),new Constant(8)),new Multiplication(new Constant(9),new Constant(2)));
        Constant c = (Constant) s.eval(vars);
        assertEquals(6, c.getValue());
    }
    
    @Test
    void testAssAdd() throws DivisionByZeroException, IllegalExpressionException {
    Environment vars = new Environment();
    Variable v = new Variable("x");
    Constant c = new Constant(1);

    Addition add1 = new Addition(new Constant(2), new Constant(3));
    Assignment a2 = new Assignment(add1, v);
    Constant c2 = new Constant(5);
    assertEquals(c2, a2.eval(vars));
    assertTrue(c2.equals(v.eval(vars)));
    assertFalse(c.equals(v.eval(vars)));


    Addition add2 = new Addition(new Addition(new Constant(1), new Constant(2)), new Variable("y"));
    Addition add3 = new Addition(new Constant(3), new Variable("y"));
    Assignment a3 = new Assignment(add2, v);
    assertEquals(add3, a3.eval(vars));
    assertTrue(add3.equals(v.eval(vars)));
    }

    // ------------------ Mixed integration tests -----------------------

    @Test
    void testSubVarDivAssAssSin() throws DivisionByZeroException, IllegalExpressionException {
        Environment vars = new Environment();
        Subtraction s = new Subtraction(
                            new Division(
                                new Assignment(
                                    new Constant(24),
                                    new Variable("x")),
                                new Sin(
                                    new Division(
                                        new Constant(Constants.namedConstants.get("pi")),
                                        new Assignment(
                                            new Constant(2),
                                            new Variable("y"))))), 
                            new Constant(2));
        Constant c = (Constant) s.eval(vars);

        assertEquals(22, c.getValue());
        assertEquals(new Constant(24), vars.get(new Variable("x")));
        assertEquals(new Constant(2), vars.get(new Variable("y")));
    }

    @Test
    void Assasssin() throws DivisionByZeroException, IllegalExpressionException {
        Environment vars = new Environment();
        Assignment a = new Assignment(
                                new Assignment(
                                    new Sin(
                                        new Constant(2)), 
                                    new Variable("x")),
                                new Variable("y"));
        Constant c = (Constant) a.eval(vars);
        assertEquals(0.9092974268256817, c.getValue());
        assertEquals(0.9092974268256817, vars.get(new Variable("x")).getValue());
        assertEquals(0.9092974268256817, vars.get(new Variable("y")).getValue());
    }

    @Test
    void testMulCosNegExpAddLog() throws DivisionByZeroException, IllegalExpressionException {
        Environment vars = new Environment();
        Multiplication m = new Multiplication(
                                    new Cos(
                                        new Negation(
                                            new Constant(2))),
                                    new Addition(
                                        new Exp(
                                            new Constant(23)),
                                        new Log(
                                            new Constant(2.718281828459045-1))));
        Constant c = (Constant) m.eval(vars);

        assertEquals(-4.0552691271554427E9, c.getValue());
    }


    // ---------------------------------------------------

    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }
}
