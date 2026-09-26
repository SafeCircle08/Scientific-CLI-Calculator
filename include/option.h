#ifndef OPTION_H
#define OPTION_H

typedef enum {
    ARITHMETIC_OPTION,
    EQUATION_OPTION,
    EQUATION_QUADRATIC_OPTION,
    DERIVATIVE_OPTION,
    SHOW_AST_OPTION,
} OPTION_TYPE;

typedef enum {
    ARITHMETIC,
    EQUATION_ALGEBRIC,
    EQUATION_QUADRATIC,
    DERIVATIVE,
    SHOW_AST
} EXPRESSION_TYPE;

typedef struct {
    int input_number;
    char name[100];
    char description[100];
} Option;

extern Option* defined_options[20];
extern int defined_options_count;

Option* create_option(int input_number, char name[100], char description[100]);

int get_option_input_number(Option* option);
char* get_option_name(Option* option);
char* get_option_description(Option* option);

void define_options(void);
void free_defined_options(void);

#endif //OPTION_H
