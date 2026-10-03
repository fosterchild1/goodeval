#include "CLI.h"
#include "Lexer.h"

int main(int argc, char** argv) {
    ParseCLI(argc, argv);
    ParseString("3+1^2*(3-2/4)+3^70000000");
    return 1;
}
