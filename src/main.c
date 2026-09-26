#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "inputs.h"
#include "option.h"
#include "format.h"

//p = "( (5 * (3 - 2^4)) - 2 )"; I JUST TYPED RANDOM NUMBERS AND I GOT 67

void show_menu() {

    define_options();

    char msg[700] = "\n********** WELCOME TO SCIENFITIC CALCULATOR **********\n\n";

    for (int i = 0; i < defined_options_count; i++) {

        char option_msg[300] = "";
        Option* op = defined_options[i];

        char description[300] = "";

        format_description(
            description,
            sizeof(description),
            get_option_description(op)
        );

        snprintf(option_msg, sizeof(option_msg),
            "%2d -> %-*s %s\n",
            get_option_input_number(op),
            FORMAT_SPACE_COUNT,
            get_option_name(op),
            description
        );
        strcat(msg, option_msg);
    }
    printf("%s", msg);
    fflush(stdout);

    free_defined_options();
}

int main(void) {

    show_menu();

    int num = get_valid_option_number_input();
    while (getchar() != '\n');

    switch (num) {
        case ARITHMETIC_OPTION: {
            p = get_expression_string(ARITHMETIC);
            Node* expr = expression();
            double result = evaluate_AST(expr);
            printf("Result: %f\n", result);
            break;
        }

        case EQUATION_OPTION: {
            p = get_expression_string(EQUATION_ALGEBRIC);
            Node* eq = equation();
            break;
        }

        case EQUATION_QUADRATIC_OPTION: {
            p = get_expression_string(EQUATION_QUADRATIC);
            Node* eq = equation();
            break;
        }

        case SHOW_AST_OPTION: {
            p = get_expression_string(SHOW_AST_OPTION);
            Node* expr = expression();
            show_AST(expr, 0);
            break;
        }

        case DERIVATIVE_OPTION: break;
        default:
    }
    return 0;
}