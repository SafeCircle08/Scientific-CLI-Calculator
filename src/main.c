#include <stdio.h>
#include "parser.h"

//p = "( (5 * (3 - 2^4)) - 2 )"; I JUST TYPED RANDOM NUMBERS AND I GOT 67

int main(void) {
    p = "e^ln(5) + (3 * 2) - cos(5)^2 * csc(2) - (3^2 / 2)";
    double result = expression();

    printf("Result: %f\n", result);

    return 0;
}