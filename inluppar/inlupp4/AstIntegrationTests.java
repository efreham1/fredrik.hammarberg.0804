import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import org.ioopm.calculator.Constants;
import org.ioopm.calculator.EvaluationVisitor;
import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;
import org.ioopm.calculator.NonConstantVariableException;

public class AstIntegrationTests {
    @BeforeAll
    static void initAll() {
    }

    @BeforeEach
    void init() {
    }


    // ------------------ Unary integration tests -----------------------

    @Test
    void testSinCos() throws DivisionByZeroException, IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        EnvironmentStack vars = new EnvironmentStack();
        EvaluationVisitor ev = new EvaluationVisitor();
        Sin s = new Sin(new Cos(new Constant(3.1415)));
        Constant c = (Constant) ev.evaluate(s,vars);
        assertEquals(-0.8414709824887332, c.getValue());
    }

    @Test
    void testNegExpLog() throws DivisionByZeroException, IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        EnvironmentStack vars = new EnvironmentStack();
        EvaluationVisitor ev = new EvaluationVisitor();
        Negation n = new Negation(new Exp(new Log(new Constant(3))));
        Constant c = (Constant) ev.evaluate(n,vars);
        assertEquals(-3.0000000000000004, c.getValue());
    }

    @Test
    void testExpNegLog() throws DivisionByZeroException, IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        EnvironmentStack vars = new EnvironmentStack();
        EvaluationVisitor ev = new EvaluationVisitor();
        SymbolicExpression n = new Exp(new Negation(new Log(new Constant(3))));
        Constant c = (Constant) ev.evaluate(n,vars);
        assertEquals(0.3333333333333333, c.getValue());
    }

    // ------------------ Binary integration tests ----------------------
    
    @Test
    void testAddDiv() throws DivisionByZeroException, IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        EnvironmentStack vars = new EnvironmentStack();
        EvaluationVisitor ev = new EvaluationVisitor();
        Addition a = new Addition(new Division(new Constant(3),new Constant(2)),new Division(new Constant(1),new Constant(2)));
        Constant c = (Constant) ev.evaluate(a,vars);
        assertEquals(2.0, c.getValue());
    }

    @Test
    void testSubMul() throws DivisionByZeroException, IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        EnvironmentStack vars = new EnvironmentStack();
        EvaluationVisitor ev = new EvaluationVisitor();
        Subtraction s = new Subtraction(new Multiplication(new Constant(3),new Constant(8)),new Multiplication(new Constant(9),new Constant(2)));
        Constant c = (Constant) ev.evaluate(s,vars);
        assertEquals(6, c.getValue());
    }
    
    @Test
    void testAssAdd() throws DivisionByZeroException, IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
    EnvironmentStack vars = new EnvironmentStack();
        EvaluationVisitor ev = new EvaluationVisitor();
    Variable v = new Variable("x");
    Constant c = new Constant(1);

    Addition add1 = new Addition(new Constant(2), new Constant(3));
    Assignment a2 = new Assignment(add1, v);
    Constant c2 = new Constant(5);
    assertEquals(c2, ev.evaluate(a2,vars));
    assertTrue(c2.equals(ev.evaluate(v,vars)));
    assertFalse(c.equals(ev.evaluate(v,vars)));


    Addition add2 = new Addition(new Addition(new Constant(1), new Constant(2)), new Variable("y"));
    Addition add3 = new Addition(new Constant(3), new Variable("y"));
    Assignment a3 = new Assignment(add2, v);
    assertEquals(add3, ev.evaluate(a3,vars));
    assertTrue(add3.equals(ev.evaluate(v,vars)));
    }

    // ------------------ Mixed integration tests -----------------------

    @Test
    void testSubVarDivAssAssSin() throws DivisionByZeroException, IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        EnvironmentStack vars = new EnvironmentStack();
        EvaluationVisitor ev = new EvaluationVisitor();
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
        Constant c = (Constant) ev.evaluate(s,vars);

        assertEquals(22, c.getValue());
        assertEquals(new Constant(24), vars.getVariable(new Variable("x")));
        assertEquals(new Constant(2), vars.getVariable(new Variable("y")));
    }

    @Test
    void Assasssin() throws DivisionByZeroException, IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        EnvironmentStack vars = new EnvironmentStack();
        EvaluationVisitor ev = new EvaluationVisitor();
        Assignment a = new Assignment(
                                new Assignment(
                                    new Sin(
                                        new Constant(2)), 
                                    new Variable("x")),
                                new Variable("y"));
        Constant c = (Constant) ev.evaluate(a,vars);
        assertEquals(0.9092974268256817, c.getValue());
        assertEquals(0.9092974268256817, vars.getVariable(new Variable("x")).getValue());
        assertEquals(0.9092974268256817, vars.getVariable(new Variable("y")).getValue());
    }

    @Test
    void testMulCosNegExpAddLog() throws DivisionByZeroException, IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        EnvironmentStack vars = new EnvironmentStack();
        EvaluationVisitor ev = new EvaluationVisitor();
        Multiplication m = new Multiplication(
                                    new Cos(
                                        new Negation(
                                            new Constant(2))),
                                    new Addition(
                                        new Exp(
                                            new Constant(23)),
                                        new Log(
                                            new Constant(2.718281828459045-1))));
        Constant c = (Constant) ev.evaluate(m,vars);

        assertEquals(-4.0552691271554427E9, c.getValue());
    }

    @Test
    void testConditional() throws DivisionByZeroException, IllegalExpressionException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException, NonConstantVariableException {
        EnvironmentStack vars = new EnvironmentStack();
        EvaluationVisitor ev = new EvaluationVisitor();
        SymbolicExpression se = new Conditional(
                new LessThan(
                    new Constant(2),
                    new Constant(4)),
                new Scope(
                    new Addition(
                        new Constant(3),
                        new Constant(8))),
                new Scope(
                    new Subtraction(
                        new Constant(3),
                        new Constant(8))));
        SymbolicExpression result = ev.evaluate(se, vars);
        assertEquals(11, result.getValue());
    }

    // ---------------------------------------------------

    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }
}
