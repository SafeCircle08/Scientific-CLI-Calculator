#include <stdio.h>
#include "parser.h"

//p = "( (5 * (3 - 2^4)) - 2 )"; I JUST TYPED RANDOM NUMBERS AND I GOT 67

int main(void) {
    p = "log_(1 + 1)(4)";
    Node* expr = expression();

    double result = evaluate_AST(expr);
    printf("Result: %f\n", result);

    return 0;
}