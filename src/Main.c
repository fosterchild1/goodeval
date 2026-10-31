#include "CLI.h"
#include "Lexer.h"
#include "Parser.h"

int main(int argc, char** argv) {
    ParseCLI(argc, argv);
    Array tokens = ParseString("3+1^2");
    TokensToAST(tokens);
    return 1;
}
