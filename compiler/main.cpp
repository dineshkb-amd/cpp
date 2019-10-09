#include <iostream>
#include <memory>
#include <token.h>

#define trace() fprintf (stdout, "%s called\n", __FUNCTION__);

static int CurTok;

static int getNextToken() {
    return CurTok = gettok();
}

#define LogError(_str) __LogError(__LINE__, _str);
std::unique_ptr<ExprAST> __LogError(int line, const char *str)  {
    fprintf (stderr, "LogError %s:%d\n", str, line);

    return nullptr;
}

#define LogErrorP(_str) __LogErrorP(__LINE__, _str);
std::unique_ptr<PrototypeAST> __LogErrorP(int line, const char *str) {
    LogError(str);
    return nullptr;
}

static std::unique_ptr<ExprAST> ParseExpression();

static std::unique_ptr<ExprAST> ParseNumberExpr() {
    trace();
    auto Result = std::make_unique<NumberExprAST>(NumVal);

    getNextToken();

    return std::move(Result);
}

static std::unique_ptr<ExprAST> ParseParenExpr() {
    trace();
    getNextToken();

    auto V = ParseExpression();
    if (!V) return nullptr;

    if (CurTok != ')') {
        return LogError("Expected ')'");
    }

    getNextToken();

    return V;
}

static std::unique_ptr<ExprAST> ParseIdentifier() {
    trace();
    std::string IdName = IdentifierStr;

    getNextToken();

    if (CurTok != '(') {
        return std::make_unique<VariableExprAST>(IdName);
    }

    // Function call
    getNextToken();

    std::vector<std::unique_ptr<ExprAST>> Args;
    if (CurTok != ')') {
        while (true) {
            if (auto Arg = ParseExpression()) {
                Args.push_back(std::move(Arg));
            } else {
                return nullptr;
            }

            if (CurTok == ')') break;
            if (CurTok != ',') 
                return LogError("Expected ')' or ',' in the arg list");

            getNextToken();
        }
    }

    getNextToken();

    return std::make_unique<CallExprAST>(IdName, std::move(Args));
}

static std::unique_ptr<ExprAST> ParsePrimary() {
    trace();
    switch (CurTok) {
        default:
            return LogError("Unknown token");
        case tok_id:
            return ParseIdentifier();
        case tok_number:
            return ParseNumberExpr();
        case '(':
            return ParseParenExpr();
    }

    return nullptr;
}

static std::unique_ptr<ExprAST> ParseBinOpRHS(int precedence, 
        std::unique_ptr<ExprAST> LHS) {
    trace();

    char Op = CurTok;

    switch (Op) {
        case '+': 
        case '-':
        case '*':
        case '/':
            {
                getNextToken();
                auto RHS = ParsePrimary();
                return std::make_unique<BinaryExprAST>(Op, std::move(LHS), 
                        std::move(RHS));
            }
        default:
            getNextToken();
            return LHS;
    }

    return nullptr;
}

static std::unique_ptr<ExprAST> ParseExpression() {
    trace();
    auto LHS = ParsePrimary();

    if (!LHS) return nullptr;

    return ParseBinOpRHS(0, std::move(LHS));
}

static std::unique_ptr<FunctionAST> HandleTopLevelExpression() {
    trace();
    if (auto E = ParseExpression()) {
        auto Proto = std::make_unique<PrototypeAST>("__anon_expr", 
                std::vector<std::string>());

        return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
    }

    return nullptr;
}

int main(int argc, char *argv[])
{
    fprintf (stderr, "ready> ");
    getNextToken();

    while(true) {
        fprintf (stderr, "ready> ");
        switch (CurTok) {
            case tok_eof:
                return 0;
            case ';': 
                getNextToken();
                break;
            case tok_def:
                getNextToken();
                break;
            case tok_extern:
                getNextToken();
                break;
            default:
                HandleTopLevelExpression();
                break;
        }
    }

    return 0;
}
