#ifndef NAL2_PARSER_H
#define NAL2_PARSER_H
#include "Scanner.h"
#include <stdexcept>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include "Token.h"

class Parser {
public:
    static void Primary(Scanner& scanner, Token& currentToken) {
        int type = currentToken.getToken();
        if (type == Scanner::tInt || type == Scanner::tHex || type == Scanner::tVariable) {
            currentToken = scanner.nextToken();
        } else if (type == Scanner::tLparen) {
            currentToken = scanner.nextToken();
            Bitwise(scanner, currentToken);
            if (currentToken.getToken() == Scanner::tRparen) {
                currentToken = scanner.nextToken();
            } else {
                throw std::runtime_error(
                    "Pričakovan ')', najden: " + currentToken.getLexem() +
                    " na (" + std::to_string(currentToken.getRow()) + "," +
                    std::to_string(currentToken.getColumn()) + ")"
                );
            }
        } else {
            throw std::runtime_error(
                "Nepričakovan simbol: " + currentToken.getLexem() +
                " na (" + std::to_string(currentToken.getRow()) + "," +
                std::to_string(currentToken.getColumn()) + ")"
            );
        }
    }

    static void Unary(Scanner& scanner, Token& currentToken) {
        int type = currentToken.getToken();
        if (type == Scanner::tPlus || type == Scanner::tMinus) {
            currentToken = scanner.nextToken();
            Primary(scanner, currentToken);
        } else {
            Primary(scanner, currentToken);
        }
    }

    static void MultiplicativeApostroph(Scanner& scanner, Token& currentToken) {
        if (currentToken.getToken() == Scanner::tTimes || currentToken.getToken() == Scanner::tDivide ||
            currentToken.getToken() == Scanner::tModulo) {
            currentToken = scanner.nextToken();
            Unary(scanner, currentToken);
            MultiplicativeApostroph(scanner, currentToken);
        }
    }

    static void AdditiveApostroph(Scanner& scanner, Token& currentToken) {
        if (currentToken.getToken() == Scanner::tPlus || currentToken.getToken() == Scanner::tMinus) {
            currentToken = scanner.nextToken();
            Multiplicative(scanner, currentToken);
            AdditiveApostroph(scanner, currentToken);
        }
    }

    static void BitwiseApostroph(Scanner& scanner, Token& currentToken) {
        if (currentToken.getToken() == Scanner::tBwand || currentToken.getToken() == Scanner::tBwor) {
            currentToken = scanner.nextToken();
            Additive(scanner, currentToken);
            BitwiseApostroph(scanner, currentToken);
        }
    }

    static void Multiplicative(Scanner& scanner, Token& currentToken) {
        Unary(scanner, currentToken);
        MultiplicativeApostroph(scanner, currentToken);
    }

    static void Additive(Scanner& scanner, Token& currentToken) {
        Multiplicative(scanner, currentToken);
        AdditiveApostroph(scanner, currentToken);
    }

    static void Bitwise(Scanner& scanner, Token& currentToken) {
        Additive(scanner, currentToken);
        BitwiseApostroph(scanner, currentToken);
    }

    static void Expr(Scanner& scanner, Token& currentToken){
        Bitwise(scanner, currentToken);
    }
};


#endif //NAL2_PARSER_H