#include <string.h>
#include <stdlib.h>
#include "option.h"

Option* defined_options[20];
int defined_options_count = 0;

Option* create_option(int input_number, char name[100], char description[100]) {

    Option* new_option = malloc(sizeof(Option));
    new_option->input_number = input_number;
    strcpy(new_option->name, name);
    strcpy(new_option->description, description);

    defined_options[defined_options_count] = new_option;
    defined_options_count++;

    return new_option;
}

int get_option_input_number(Option* option) {
    return option->input_number;
}

char* get_option_name(Option* option) {
    return option->name;
}

char* get_option_description(Option* option) {
    return option->description;
}

void define_options(void) {
    Option* option_1 = create_option(
       ARITHMETIC_OPTION,
       "Arithmetic Expression",
       "Evaluate a simple arithmetic expression.\n"
       "ex: log_2(5)(3 + ln(e)) * pi - cot(4.2)"
   );

    Option* option_2 = create_option(
        EQUATION_OPTION,
        "Resolve equation",
        "Evaluates an algebric equation given one variable.\n"
        "ex: 3 + (x * 5) = 2"
    );

    Option* option_3 = create_option(
        EQUATION_QUADRATIC_OPTION,
        "Resolve quadratic equation",
        "Evaluates a quadratic equation given one variable.\n"
        "ex: x^2 - 2*x + 5 = 0"
    );

    Option* option_4 = create_option(
        SHOW_AST_OPTION,
        "Show AST (algebric equation)",
        "Given any sequence (of valid) number / symbols\n"
        "draws the AST"
    );
}

void free_defined_options(void) {
    for (int i = 0; i < defined_options_count; i++) {
        Option* op = defined_options[i];
        if (op != nullptr) free(defined_options[i]);
    }
}