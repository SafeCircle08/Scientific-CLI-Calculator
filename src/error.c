#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"

void show_error(ERROR_TYPE error_type) {
    char msg[50];
    switch (error_type) {
        case SYNTAX_ERROR:
            strcpy(msg, "Syntax error");
        break;
        case MATH_ERROR:
            strcpy(msg, "Math error");
        break;
        case UNKNOWN_FUNCTION:
            strcpy(msg, "Unknown function");
        break;
        case UNKNOWN_VARIABLE:
            strcpy(msg, "Unknown variable");
        break;
        case INVALID_ARGUMENT:
            strcpy(msg, "Invalid argument");
        break;
    }
    printf("%s\n", msg);
}

void throw_error(ERROR_TYPE error_type, const char* message) {
    show_error(error_type);
    printf("%s\n", message);
    exit(-1);
}

void throw_parenthesis_error(void) {
    throw_error(SYNTAX_ERROR, PARENTHESIS_ERROR);
}

void throw_invalid_function_error(void) {
    throw_error(UNKNOWN_FUNCTION, INVALID_FUNCTION_ERROR_STRING);
}

void throw_division_by_zero_error(void) {
    throw_error(MATH_ERROR, DIVIDE_BY_ZERO_ERROR_STRING);
}

void throw_invalid_argument_error(void) {
    throw_error(INVALID_ARGUMENT, INVALID_ARGUMENT_ERROR_STRING);
}