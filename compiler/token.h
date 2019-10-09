#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <iostream>
#include <memory>
#include <vector>

enum Token {
    tok_eof = -1, 
    tok_def = -2, 
    tok_extern = -3, 
    tok_id = -4, 
    tok_number = -5,
};

class ExprAST {
 public:
   virtual ~ExprAST() {}
};

class NumberExprAST : public ExprAST {
    double Val;

 public:
    NumberExprAST(double val) : Val(val) {}
};

class VariableExprAST : public ExprAST {
    std::string Name;

 public:
    VariableExprAST(const std::string &Name) : Name(Name) {}
};

class BinaryExprAST : public ExprAST {
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;


 public:
    BinaryExprAST(char op, std::unique_ptr<ExprAST> LHS, 
            std::unique_ptr<ExprAST> RHS) : 
        Op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

class CallExprAST : public ExprAST {
    std::string Callee; 
    std::vector<std::unique_ptr<ExprAST>> Args;

 public:
    CallExprAST(const std::string &Callee, 
            std::vector<std::unique_ptr<ExprAST>> Args) :
        Callee(Callee), Args(std::move(Args)) {}
};

class PrototypeAST {
    std::string Name;
    std::vector<std::string> Args;

 public:
    PrototypeAST(const std::string &name, std::vector<std::string> Args)
        : Name(name), Args(std::move(Args)) {}
};

class FunctionAST {
    std::unique_ptr<PrototypeAST> Prototype; 
    std::unique_ptr<ExprAST> Body;

 public:

    FunctionAST(std::unique_ptr<PrototypeAST> Prototype, 
            std::unique_ptr<ExprAST> Body) 
        : Prototype(std::move(Prototype)), Body(std::move(Body)) {}
};

extern std::string IdentifierStr;
extern double NumVal;
extern int gettok();

#endif //_TOKEN_H_
