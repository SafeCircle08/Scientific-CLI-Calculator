#include <stdio.h>
#include <string.h>
#include "inputs.h"
#include "option.h"

char* get_expression_string(EXPRESSION_TYPE type) {
    static char expression[500];
    const char* prompt;

    switch (type) {
        case ARITHMETIC: prompt = "Insert arithmetic expression: "; break;
        case EQUATION_ALGEBRIC: prompt = "Insert equation: "; break;
        case EQUATION_QUADRATIC: prompt = "Insert quadratic equation: "; break;
        case SHOW_AST: prompt = "Insert arithmetic expression: "; break;
        default: prompt = "How?"; break;
    }

    printf("%s", prompt);
    fflush(stdout);

    if (fgets(expression, sizeof(expression), stdin) == NULL)
        return NULL;

    expression[strcspn(expression, "\n")] = '\0';
    return expression;
}

bool input_number_is_valid(int n) {
    return ((n >= 0) && (n <= defined_options_count));
}

int get_valid_option_number_input() {
    int n;

    printf("Your input: ");
    fflush(stdout);

    while (scanf("%d", &n) != 1 || !input_number_is_valid(n)) {
        printf("Invalid input!\n");
        printf("Your input: ");
        fflush(stdout);

        while (getchar() != '\n');
    }

    return n;
}