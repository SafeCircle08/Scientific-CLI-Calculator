#include <stdio.h>
#include "math.h"
#include "parser.h"

#include <string.h>

#include "calculator.h"

const char* p;

bool char_is_number(void) { return (*p >= '0' && *p <= '9'); }
bool char_is(const char c) { return (*p == c); }
bool char_is_alpha() { return (*p >= 'a' && *p <= 'z') || (*p == '_'); }
void char_show() { printf("%c\n", *p); }
void char_increment() { p++; }
void char_skip_spaces(void) { while (*p == ' ') char_increment(); }
int char_to_int() { return *p - '0'; }

char function_name[20];
int i = 0;
double number = 0.0;

double collect_number() {
    char letter_n[5];

    double n = 0.0;
    if (char_is_alpha()) {
        while (char_is_alpha()) {
            letter_n[i] = *p;
            i++;
            char_increment();
        }
        letter_n[i] = '\0';

        if (strcmp(letter_n, "e") == 0) {
            return e;
        }
        else if (strcmp(letter_n, "pi") == 0) return M_PI;
    }

    while (char_is_number()) {
        n = n * 10 + (*p - '0');
        char_increment();
    }

    if (char_is('.')) {
        char_increment();
        double decimal = 0.1;

        while (char_is_number()) {
            n += (*p - '0') * decimal;
            decimal *= 0.1;
            char_increment();
        }
    }
    return n;
}

double evaluate_parentesis() {
    double number = 0;

    if (char_is('(')) char_increment();

    number = expression();

    char_skip_spaces();
    if (char_is(')')) char_increment();
    return number;
}

double evaluate_parentesis_type(const char c1, const char c2) {
    double number;

    if (char_is(c1)) char_increment();

    number = collect_number();

    char_skip_spaces();
    if (char_is(c2)) char_increment();
    return number;
}

void manage_trig_funcs(double *number, const char *trig_func_name) {
    double argument = evaluate_parentesis();

    enum TRIG_FUNCS func = get_trig_func(trig_func_name);
    switch (func) {
        case SIN: *number = evaluate_trig_func(sin, argument); break;
        case COS: *number = evaluate_trig_func(cos, argument); break;
        case TAN: *number = evaluate_trig_func(tan, argument); break;

        case ARCSIN: *number = evaluate_trig_func(asin, argument); break;
        case ARCCOS: *number = evaluate_trig_func(acos, argument); break;
        case ARCTAN: *number = evaluate_trig_func(atan, argument); break;

        case SEC: *number = evaluate_trig_func(sec, argument); break;
        case CSC: *number = evaluate_trig_func(csc, argument); break;
        case COT: *number = evaluate_trig_func(cot, argument); break;
    }
}

void manage_log_funcs(double *number, const char *log_func_name) {
    enum LOGARITHMIC_FUNCS func = get_log_func(log_func_name);

    switch (func) {
        double argument;
        case LOG:
            argument = evaluate_parentesis();
            *number = evaluate_log_func(log10, argument);
        break;
        case LOG_BASE:
            double base;
            if (char_is('(')) {
                base = evaluate_parentesis();
            } else base = collect_number();

            argument = evaluate_parentesis();
            *number = log(argument) / log(base);
        break;
        case LOG_NATURAL:
            argument = evaluate_parentesis();
            *number = evaluate_log_func(ln, argument);
        break;
    }
}

//Manages numbers
double factor(void) {
    char_skip_spaces();
    char function_name[20];
    int i = 0;
    double number = 0.0;

    if (char_is_number() || char_is('.')) {
        number = collect_number();
    }

    if (char_is_alpha()) {
        while (char_is_alpha()) {
            function_name[i] = *p;
            i++;
            char_increment();
        }
        function_name[i] = '\0';

        if (strcmp(function_name, "e") == 0) number = e;
        else if (strcmp(function_name, "pi") == 0) {
            number = M_PI;
        }

        if (is_trig_func(function_name)) manage_trig_funcs(&number, function_name);
        if (is_log_func(function_name)) manage_log_funcs(&number, function_name);

        if (is_root_func(function_name)) {
            double root_index = collect_number();
            double argument = evaluate_parentesis();
            number = evaluate_root_func(argument, root_index);
        }

        if (is_sqrt_func(function_name)) {
            double argument = evaluate_parentesis();
            number = evaluate_root_func(argument, 2.0);
        }
    }

    if (char_is('(')) number = evaluate_parentesis();

    if (char_is('!')) {
        double argument = number;
        number = factorial(argument);

        char_increment();
    }

    if (char_is('^')) {
        double base = number;
        double exponent;
        number = 1.0;

        char_increment();

        if (char_is('(')) exponent = evaluate_parentesis();
        else exponent = collect_number();

        char_increment();
        number = pow(base, exponent);
    }
    return number;
}

//Manages / and *
double term(void) {
    char_skip_spaces();
    double result = factor();
    char_skip_spaces();

    while (char_is('*') || char_is('/')) {
        printf("Ok *\n");
        char operator = *p;
        char_increment();
        char_skip_spaces();

        double value = factor();
        if (operator == '*') result = mul(result, value);
        else if (operator == '/') result = div(result, value);

        char_skip_spaces();
    }
    return result;
}

double expression(void) {
    char_skip_spaces();
    double result = term();
    char_skip_spaces();

    while (char_is('+') || char_is('-')) {
        char operator = *p;
        char_increment();
        char_skip_spaces();
        double value = term();

        if (operator == '+') result = sum(result, value);
        else if (operator == '-') result = sub(result, value);

        char_skip_spaces();
    }
    return result;
}