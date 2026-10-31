#include <stdlib.h>
#include <stdbool.h>
#include "Lexer.h"
#include "Parser.h"
#include "Utils/array.h"
#include "Utils/Util.h"
#include <stdio.h>

const int TOKEN_ORDER[512] = {
    [ADD] = 1,
    [SUB] = 1,
    [MUL] = 2,
    [DIV] = 2,
    [EXP] = 3
};

const OPERATOR_TYPE TOKEN_TO_OP[512] = {
    [ADD] = OP_ADD,
    [SUB] = OP_SUB,
    [MUL] = OP_MUL,
    [DIV] = OP_DIV,
    [EXP] = OP_EXP
};

bool IsOperatorToken(TOKEN_TYPE t) {
    return (t == ADD || t == SUB || t == MUL || t == DIV || t == EXP);
}

ExprNode* ValueTokenToNode(Token tok) {
    ExprNode* valNode = xmalloc(sizeof(ExprNode));
    valNode->ndType = ND_NUM;
    valNode->nodeVal.value = atoi(tok.value);

    return valNode;
}

ExprNode* SingleTokensToNode(Token tokenL, Token tokenR, OPERATOR_TYPE opType) {
    ExprNode* valNodeL = ValueTokenToNode(tokenL);    
    ExprNode* valNodeR = ValueTokenToNode(tokenR);
    
    ExprNode* operationNode = xmalloc(sizeof(ExprNode));
    operationNode->ndType = ND_BINARY_EXPR;
    operationNode->nodeVal.binaryExpr = &(BinaryExpr){
        .left = valNodeL,
        .opType = opType,
        .right = valNodeR,
    };

    return operationNode;
}

Array GetOperand(Array tokens, int operatorIdx, bool increaseIdx) {
    Token* tokenData = (Token*)tokens.data;

    Array operand = Array_New(sizeof(Token));
   
    int incr = (increaseIdx ? 1 : -1);
    int bracketDepth = 0;

    int selfOrder = TOKEN_ORDER[tokenData[operatorIdx].token];

    for (int i = operatorIdx + incr; (i < tokens.len && i >= 0); i+=incr) {
        Token tok = tokenData[i];
        TOKEN_TYPE type = tok.token;
        if (IsOperatorToken(type) && bracketDepth == 0 && TOKEN_ORDER[type] <= selfOrder) break;
        
        Array_Insert(&operand, &tok);

        // handle bracket depth (e.g. (3+(5^(3-2)+7)-8)
        if (type == LEFT_PARANTH) bracketDepth++; 
        else if (type == RIGHT_PARANTH) bracketDepth--;
    }
    
    return operand;
}

ExprNode* TokensToAST(Array tokens) {
    Token* tokenData = (Token*)tokens.data;

    ExprNode* tree = xmalloc(sizeof(ExprNode));
    tree->ndType = ND_BINARY_EXPR;

    int i = 0;
    while (i < tokens.len) {
        Token tok = tokenData[i];
        if (!IsOperatorToken(tok.token)) { i++; continue; }
    
        Array operandL = GetOperand(tokens, i, false);
        Token* tdL = (Token*)operandL.data;
        Array operandR = GetOperand(tokens, i, true);
        Token* tdR = (Token*)operandR.data;

        if (operandL.len == 1 && operandR.len == 1) {
            return SingleTokensToNode(tdL[0], tdR[0], TOKEN_TO_OP[tok.token]);
        }

        printf("Llen: %d, Rlen: %d\n", operandL.len, operandR.len);
        for (int j = 0; j < operandL.len; j++)
            printf("L: %s\n", tdL[j].value);
        printf("LR OPERATOR: %s\n", tok.value);
        for (int j = 0; j < operandR.len; j++)
            printf("R: %s\n", tdR[j].value);

        ExprNode* nodeL = TokensToAST(operandL);
        ExprNode* nodeR = TokensToAST(operandR);
        tree->nodeVal.binaryExpr = &(BinaryExpr){.left = nodeL, .opType = TOKEN_TO_OP[tok.token], .right = nodeR};
        PrintExprNode(*nodeL); PrintExprNode(*nodeR);

        i += operandR.len;
    }

    return tree;
}
