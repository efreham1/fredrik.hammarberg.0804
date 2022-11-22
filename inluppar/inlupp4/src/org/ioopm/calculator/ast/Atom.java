package org.ioopm.calculator.ast;

/**
* Abstract class for atomic expression nodes in the AST
*/
public abstract class Atom extends SymbolicExpression {
    public Atom(String name) {
        super(name);
    }
}