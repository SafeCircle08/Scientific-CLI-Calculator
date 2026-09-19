#include "calculator.h"
#include "math.h"
#include "string.h"

const double e = 2.71828182845904523536;

double sum(double a, double b) { return (a + b); }
double sub(double a, double b) { return (a - b); }
double mul(double a, double b) { return (a * b); }
double div(double a, double b) { return (a / b); }

double sec(double arg) { return (1 / cos(arg)); }
double csc(double arg) { return (1 / sin(arg)); }
double cot(double arg) { return (1 / tan(arg)); }

double log10(double arg) { return log_base(arg, 10); };
double log_base(double arg, double base) { return (log(arg) / log(base)); };
double ln(double arg) { return log(arg); };

bool is_trig_func(const char *name) {
    return (
        (strcmp(name, "sin") == 0) ||
        (strcmp(name, "cos") == 0) ||
        (strcmp(name, "tan") == 0) ||

        (strcmp(name, "arcsin") == 0) ||
        (strcmp(name, "arccos") == 0) ||
        (strcmp(name, "arctan") == 0) ||

        (strcmp(name, "sec") == 0) ||
        (strcmp(name, "csc") == 0) ||
        (strcmp(name, "cot") == 0)
    );
}

bool is_log_func(const char *name) {
    return (
        (strcmp(name, "log") == 0) ||
        (strcmp(name, "log_") == 0) ||
        (strcmp(name, "ln") == 0)
    );
}

double evaluate_log_func(double (*log_func)(double), double argument) {
    return log_func(argument);
}

enum TRIG_FUNCS get_trig_func(const char *name) {
    if (strcmp(name, "sin") == 0) return SIN;
    if (strcmp(name, "cos") == 0) return COS;
    if (strcmp(name, "tan") == 0) return TAN;

    if (strcmp(name, "arcsin") == 0) return ARCSIN;
    if (strcmp(name, "arccos") == 0) return ARCCOS;
    if (strcmp(name, "arctan") == 0) return ARCTAN;

    if (strcmp(name, "sec") == 0) return SEC;
    if (strcmp(name, "csc") == 0) return CSC;
    if (strcmp(name, "cot") == 0) return COT;
}

enum LOGARITHMIC_FUNCS get_log_func(const char *name) {
    if (strcmp(name, "log") == 0) return LOG;
    if (strcmp(name, "log_") == 0) return LOG_BASE;
    if (strcmp(name, "ln") == 0) return LOG_NATURAL;
}

double evaluate_trig_func(double (*trig_func)(double), double argument) {
    double result = 0;
    double radians = argument * M_PI / 180.0;
    result = trig_func(radians);
    return result;
}
