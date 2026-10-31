#pragma once

#include "Utils/array.h"

typedef enum {
    ND_NUM, ND_VARIABLE, ND_BINARY_EXPR,
} NODE_TYPE;

typedef enum {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_EXP, 
} OPERATOR_TYPE;

typedef struct ExprNode ExprNode;

typedef struct {
    ExprNode* left;
    OPERATOR_TYPE opType;
    ExprNode* right;
} BinaryExpr;

struct ExprNode {
    NODE_TYPE ndType;

    union {
        double value;
        BinaryExpr* binaryExpr;
    } nodeVal;
};

ExprNode* TokensToAST(Array tokens);
