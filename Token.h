// DATOTEKA: Token.h
#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

using namespace std;

class Token {
private:
    string lexem; // leksikalni element 
    int column;   // stolpec izvorne datoteke, kjer je prvi znak lexema 
    int row;      // vrstica izvorne datoteke, kjer je prvi znak lexema 
    int token;    // osnovni leksikalni simbol 
    bool eof;     // konec datoteke 

public:
    // konstruktor 
    Token(const string& aLexem, int aColumn, int aRow, int aToken, bool aEof)
        : lexem(aLexem), column(aColumn), row(aRow), token(aToken), eof(aEof) {  
            
           }
    
    // privzeti konstruktor 
    Token() : lexem("") {
    }
    
    // vrni leksikalni element 
    const string getLexem() const { return lexem; }
    
    // vrni vrstico lexema 
    const int getRow() const { return row; }
    
    // vrni stolpec lexema 
    const int getColumn() const { return column; }
    
    // vrni osnovni leksikalni element 
    const int getToken() const { return token; }
    
    // vrni ali konec datoteke 
    const bool isEof() const { return eof; }
    
    // izpis osnovnega leksikalnega simbola 
    friend ostream& operator<<(ostream &out, const Token& aToken) {
        out << aToken.getLexem() << " " << aToken.getToken()
            << " (" << aToken.getRow() << ", " << aToken.getColumn() << ") " 
            << (aToken.isEof() ? "true" : "false");
        return out;
    }
};
#endif // TOKEN_H 