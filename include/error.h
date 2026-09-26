//
// Created by Utente on 25/09/2026.
//

#ifndef ERROR_H
#define ERROR_H

#define PARENTHESIS_ERROR ("Invalid Parenthesis Placement!")
#define INVALID_FUNCTION_ERROR_STRING ("No Function with that Name exists!")
#define DIVIDE_BY_ZERO_ERROR_STRING ("Cannot divide by zero!")
#define INVALID_ARGUMENT_ERROR_STRING ("Invalid argument for a function!")

typedef enum ERROR_TYPE {
    SYNTAX_ERROR,
    MATH_ERROR,
    UNKNOWN_FUNCTION,
    UNKNOWN_VARIABLE,
    INVALID_ARGUMENT
} ERROR_TYPE;

void show_error(ERROR_TYPE type);
void throw_error(ERROR_TYPE type, const char* message);

void throw_parenthesis_error(void);
void throw_invalid_function_error(void);
void throw_division_by_zero_error(void);
void throw_invalid_argument_error(void);

#endif //ERROR_H
