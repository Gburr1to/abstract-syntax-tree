// DATOTEKA: Scanner.h
#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"

class Scanner {
private:
    istream* input;      
    Token lastToken;     
    int row;             
    int column;          

    const static int maxState = 16;
    const static int noEdge = -1;    
    const static int startState = 0; 

    int automata[maxState + 1][256]; 
    int finite[maxState + 1];        

    void initAutomata() {
        for (int i = 0; i <= maxState; i++) {
            for (int j = 0; j < 256; j++)                 
                automata[i][j] = noEdge;
            finite[i] = tLexError; // Vsa stanja so privzeta nekončna
        }

        // PRESLEDKI IN NOVE VRSTICE (Stanje 15) -> tIgnore
        automata[0][' '] = automata[0]['\n'] = automata[0]['\t'] = automata[0]['\r'] = 15;
        automata[15][' '] = automata[15]['\n'] = automata[15]['\t'] = automata[15]['\r'] = 15;
        finite[15] = tIgnore;

        for (int i = '0'; i <= '9'; i++) {
            automata[0][i] = 1;
            automata[1][i] = 1;
        }
        finite[1] = tInt;

        // HEX: #[0-9a-fA-F]+ (Stanje 2 za '#' ni končno, Stanje 3 # + cifre/črke) -> tHex
        automata[0]['#'] = 2;
        for (int i = '0'; i <= '9'; i++) automata[2][i] = automata[3][i] = 3;
        for (int i = 'a'; i <= 'f'; i++) automata[2][i] = automata[3][i] = 3;
        for (int i = 'A'; i <= 'F'; i++) automata[2][i] = automata[3][i] = 3;
        finite[3] = tHex;

        // VARIABLE: [a-zA-Z]+[0-9]* (Stanje 4 za črke, Stanje 5 za cifre na koncu - ne moremo se vrniti iz 5 v 4) -> tVariable
        for (int i = 'a'; i <= 'z'; i++) { automata[0][i] = automata[4][i] = 4; }
        for (int i = 'A'; i <= 'Z'; i++) { automata[0][i] = automata[4][i] = 4; }
        for (int i = '0'; i <= '9'; i++) { automata[4][i] = automata[5][i] = 5; }
        finite[4] = tVariable;
        finite[5] = tVariable;

        automata[0]['+'] = 6; finite[6] = tPlus;
        automata[0]['-'] = 7; finite[7] = tMinus;
        automata[0]['*'] = 8; finite[8] = tTimes;
        automata[0]['/'] = 9; finite[9] = tDivide; // Če je samo en '/', je deljenje
        automata[0]['%'] = 10; finite[10] = tModulo;
        automata[0]['&'] = 11; finite[11] = tBwand;
        automata[0]['|'] = 12; finite[12] = tBwor;
        automata[0]['('] = 13; finite[13] = tLparen;
        automata[0][')'] = 14; finite[14] = tRparen;

        automata[9]['/'] = 16; // Če za '/' sledi še en '/', stanje 16 (Komentar)
        for (int j = 0; j < 256; j++) automata[16][j] = 16; //vzame tudi presledke
        automata[16]['\n'] = noEdge; // dokler ne pride do nove vrstice.
        finite[16] = tIgnore; // Komentarje prezremo
    }

protected:
    int getNextState(int aState, int aChar) const {         
        if (aChar == -1) return noEdge;         
        return automata[aState][aChar];     
    }

    bool isFiniteState(int aState) const {         
        return finite[aState] != tLexError;     
    }

    int getFiniteState(int aState) const {         
        return finite[aState];     
    }

private:
    int peek() { return input->peek(); }

    int read() {         
        int temp = input->get();         
        column++;         
        if (temp == '\n') { row++; column = 1; }
        return temp;     
    }

    bool eof() { return peek() == -1; }

    Token nextTokenImp() {         
        int currentState = startState;         
        string lexem;         
        int startColumn = column;         
        int startRow = row; 
        
        do {             
            int tempState = getNextState(currentState, peek());             
            if (tempState != noEdge) {                 
                currentState = tempState;                 
                lexem += (char)read();             
            } else {
                if (isFiniteState(currentState)) {                     
                    Token token(lexem, startColumn, startRow, getFiniteState(currentState), eof());                     
                    if (token.getToken() == tIgnore) {
                        return nextToken();
                    } else {
                        return token;                     
                    }
                } else {
                    return Token(lexem, startColumn, startRow, tLexError, eof());                 
                }
            }
        } while (true);     
    }

public:
    const static int tLexError = -1;
    const static int tIgnore = 0;        
    const static int tInt = 1;       
    const static int tHex = 2;
    const static int tVariable = 3;
    const static int tPlus = 4;
    const static int tMinus = 5;
    const static int tTimes = 6;
    const static int tDivide = 7;
    const static int tModulo = 8;
    const static int tBwand = 9;
    const static int tBwor = 10;
    const static int tLparen = 11;
    const static int tRparen = 12;

    Scanner(istream *aInput) {         
        row = 1;         
        column = 1;         
        initAutomata();         
        input = aInput;     
    }

    Token nextToken() { return lastToken = nextTokenImp(); }
    Token currentToken() { return lastToken; }
};
#endif // SCANNER_H