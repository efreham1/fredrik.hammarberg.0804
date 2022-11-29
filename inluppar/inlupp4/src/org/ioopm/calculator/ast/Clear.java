package org.ioopm.calculator.ast;
import org.ioopm.calculator.Visitor;
import org.ioopm.calculator.NamedConstantAssignmentException;
import org.ioopm.calculator.ReassignmentException;

/**
* Clear command node
*/
public class Clear extends Command {
    private static final Clear theInstance = new Clear();

    private Clear() {
        super("Clear");
    }

    public static Clear instance() {
        return theInstance;
    }

    @Override
    public SymbolicExpression accept(Visitor v) throws IllegalExpressionException, DivisionByZeroException, NamedConstantAssignmentException, ReassignmentException, RootEnvironmentException {
    return v.visit(this);
}
}