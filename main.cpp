#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "AST.h"
#include <stdexcept>
#include <exception>

using namespace std;

void testTree(Expr* tree) {
    string generatedCode = tree->toString();
    cout << "Generirana koda: " << generatedCode << endl;

    istringstream inputString(generatedCode); //istringstream za razliko od ifstream ne rabi dejanske datoteke, samo string vhod
    Scanner scanner(&inputString);
    Token currentToken = scanner.nextToken();

    try {
        Parser::Expr(scanner, currentToken);
        if (currentToken.isEof() && currentToken.getLexem() == "") {
            cout << "Rezultat Parserja: ACCEPT" << endl;
        } else {
            cout << "Rezultat Parserja: REJECT" << endl;
        }
    } catch (std::exception& e) {
        cout << "Rezultat Parserja: REJECT (" << e.what() << ")" << endl;
    }
    cout << "------------------------------------------------" << endl;

    delete tree;
}

int main() {
    cout << "=== TESTIRANJE ABSTRAKTNEGA SINTAKTIČNEGA DREVESA ===" << endl << endl;

    // Test 1: plus(times(int(1),int(2)),int(3))
    testTree(
        new PlusExpr(
            new TimesExpr(new IntExpr(1), new IntExpr(2)),
            new IntExpr(3)
        )
    );

    // Test 2: times(int(1),plus(int(2),hex('#F1')))
    testTree(
        new TimesExpr(
            new IntExpr(1),
            new PlusExpr(new IntExpr(2), new HexExpr("#F1"))
        )
    );

    // Test 3: minus(minus(int(4),int(1)),int(1))
    testTree(
        new MinusExpr(
            new MinusExpr(new IntExpr(4), new IntExpr(1)),
            new IntExpr(1)
        )
    );

    // Test 4: divides(int(4),plus(variable('abc'),int(1)))
    testTree(
        new DividesExpr(
            new IntExpr(4),
            new PlusExpr(new VarExpr("abc"), new IntExpr(1))
        )
    );

    // Test 5: bwand(plus(variable('x'),variable('y')),bwor(int(2),int(2)))
    testTree(
        new BwandExpr(
            new PlusExpr(new VarExpr("x"), new VarExpr("y")),
            new BworExpr(new IntExpr(2), new IntExpr(2))
        )
    );

    // Test 6: plus(int(1),int(2))
    testTree(
        new PlusExpr(new IntExpr(1), new IntExpr(2))
    );

    return 0;
}