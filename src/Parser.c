#include <stdlib.h>
#include <stdbool.h>
#include "Lexer.h"
#include "Parser.h"
#include "Utils/array.h"

bool IsOperatorToken(TOKEN_TYPE t) {
    return (t == ADD || t == SUB || t == MUL || t == DIV || t == EXP);
}


Array GetOperand(Array tokens, int operatorIdx, bool increaseIdx) {
   Token* tokenData = (Token*)tokens.data;

   Array operand = Array_New(sizeof(Token));
   
   int incr = (increaseIdx ? 1 : -1);
   int bracketDepth = 0;

   for (int i = operatorIdx + incr; i < tokens.len; i+=incr) {
        Token tok = tokenData[i];
        TOKEN_TYPE type = tok.token;

        // handle bracket depth (e.g. (3+(5^(3-2)+7)-8)
        if (type == LEFT_PARANTH) { bracketDepth++; continue; }
        else if (type == RIGHT_PARANTH) { bracketDepth--; continue; }

   }

   return operand;
}

ExprNode TokensToAST(Array tokens) {
    Token* tokenData = (Token*)tokens.data;

    ExprNode tree = {.ndType = ND_BINARY_EXPR, .nodeVal = {.binaryExpr = NULL}};

    for (int i = 0; i < tokens.len; i++) {
        Token tok = tokenData[i];
        if (!IsOperatorToken(tok.token)) continue;

    }
    
    return tree;
}
