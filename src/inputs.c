#include <stdio.h>
#include <string.h>
#include "inputs.h"

char* get_expression(void) {
    static char expr[500];

    printf("Insert expression: ");
    fflush(stdout);

    if (fgets(expr, sizeof(expr), stdin) == NULL)
        return NULL;


    expr[strcspn(expr, "\n")] = '\0';

    return expr;
}
