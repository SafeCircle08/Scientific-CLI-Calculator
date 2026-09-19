#include <stdio.h>
#include "parser.h"

//p = "( (5 * (3 - 2^4)) - 2 )"; I JUST TYPED RANDOM NUMBERS AND I GOT 67

int main(void) {
    p = "2^(e + (pi / 2))";
    double result = expression();

    printf("Result: %f\n", result);

    return 0;
}