#ifndef VAJA10_AST_H
#define VAJA10_AST_H


#include <string>

using namespace std;

class Expr {
public:
    virtual ~Expr() = default;
    virtual string toString() const = 0;
};

// TERMINALI

class IntExpr : public Expr {
    int value;
public:
    IntExpr(int v) : value(v) {}
    string toString() const override { return to_string(value); }
};

class HexExpr : public Expr {
    string value;
public:
    HexExpr(const string& v) : value(v) {}
    string toString() const override { return value; }
};

class VarExpr : public Expr {
    string name;
public:
    VarExpr(const string& n) : name(n) {}
    string toString() const override { return name; }
};

// OPERACIJE

class BinOpExpr : public Expr {
protected:
    Expr* left;
    Expr* right;
    string op;
public:
    BinOpExpr(Expr* l, Expr* r, string o) : left(l), right(r), op(o) {}
    ~BinOpExpr() {
        delete left;
        delete right;
    }
    string toString() const override {
        return "(" + left->toString() + " " + op + " " + right->toString() + ")";
    }
};

class PlusExpr : public BinOpExpr {
public: PlusExpr(Expr* l, Expr* r) : BinOpExpr(l, r, "+") {}
};

class MinusExpr : public BinOpExpr {
public: MinusExpr(Expr* l, Expr* r) : BinOpExpr(l, r, "-") {}
};

class TimesExpr : public BinOpExpr {
public: TimesExpr(Expr* l, Expr* r) : BinOpExpr(l, r, "*") {}
};

class DividesExpr : public BinOpExpr {
public: DividesExpr(Expr* l, Expr* r) : BinOpExpr(l, r, "/") {}
};

class ModuloExpr : public BinOpExpr {
public: ModuloExpr(Expr* l, Expr* r) : BinOpExpr(l, r, "%") {}
};

class BwandExpr : public BinOpExpr {
public: BwandExpr(Expr* l, Expr* r) : BinOpExpr(l, r, "&") {}
};

class BworExpr : public BinOpExpr {
public: BworExpr(Expr* l, Expr* r) : BinOpExpr(l, r, "|") {}
};


#endif //VAJA10_AST_H