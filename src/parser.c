#include "math.h"
#include "parser.h"
#include "calculator.h"

const char* p;

bool char_is_number(void) { return (*p >= '0' && *p <= '9'); }
bool char_is(const char c) { return (*p == c); }
bool char_is_alpha() { return (*p >= 'a' && *p <= 'z') || (*p == '_'); }
void char_show() { printf("%c\n", *p); }
void char_increment() { p++; }
void char_skip_spaces(void) { while (*p == ' ') char_increment(); }
int char_to_int() { return *p - '0'; }

double evaluate_parentesis() {
    double number = 0;
    char_increment();

    number = expression();

    char_skip_spaces();
    if (char_is(')')) char_increment();
    return number;
}

void manage_trig_funcs(double *number, const char *trig_func_name) {
    char_increment();
    double argument = expression();
    if (char_is(')')) char_increment();

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
        char_increment();
        argument = expression();
        *number = evaluate_log_func(log10, argument);
        if (char_is(')')) char_increment();
        break;
        case LOG_BASE:
        double base = 0;
        if (char_is_number()) {
            while (char_is_number()) {
                base = base * 10 + (*p - '0');
                char_increment();
            }
        }
        argument = expression();
        *number = log(argument) / log(base);
        if (char_is(')')) char_increment();
        break;
        case LOG_NATURAL:
        char_increment();
        argument = expression();
        *number = evaluate_log_func(ln, argument);
        if (char_is(')')) char_increment();
        break;
    }
}

//Manages numbers
double factor(void) {
    char_skip_spaces();
    char function_name[20];
    int i = 0;
    double number = 0;

    if (char_is_number()) {
        while (char_is_number()) {
            number = number * 10 + (*p - '0');
            char_increment();
        }
    }

    if (char_is_alpha()) {
        while (char_is_alpha()) {
            if (char_is('e')) {
                number = e;
                char_increment();
            }
            function_name[i] = *p;
            i++;
            char_increment();
        }
        function_name[i] = '\0';

        if (is_trig_func(function_name)) manage_trig_funcs(&number, function_name);
        if (is_log_func(function_name)) manage_log_funcs(&number, function_name);
    }

    if (char_is('(')) number = evaluate_parentesis();

    if (char_is('^')) {
        double base = number;
        number = 1;

        char_increment();
        int exponent = char_to_int();
        char_increment();
        for (int i = 0; i < exponent; i++) number = number * base;
    }
    return number;
}

//Manages / and *
double term(void) {
    char_skip_spaces();
    double result = factor();
    char_skip_spaces();

    while (char_is('*') || char_is('/')) {
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