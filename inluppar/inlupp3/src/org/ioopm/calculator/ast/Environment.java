package org.ioopm.calculator.ast;

import java.util.HashMap;

/**
* Data structure in which to store variables for the AST
*/
public class Environment extends HashMap<Variable, SymbolicExpression> {}
