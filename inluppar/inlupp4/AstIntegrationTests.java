
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

import org.ioopm.calculator.ast.*;


public class AstIntegrationTests {
    @BeforeAll
    static void initAll() {
    }

    @BeforeEach
    void init() {
    }

    // 
    /*
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
    */

    // ---------------------------------------------------



    @AfterEach
    void tearDown() {
    }

    @AfterAll
    static void tearDownAll() {
    }
}