#ifndef CALCULATOR_H
#define CALCULATOR_H

extern const double e;

double sum(double a, double b);
double sub(double a, double b);
double mul(double a, double b);
double div(double a, double b);

double sec(double arg);
double csc(double arg);
double cot(double arg);

double log10(double arg);
double log_base(double arg, double base);
double ln(double arg);

enum TRIG_FUNCS {
    SIN,
    COS,
    TAN,

    ARCSIN,
    ARCCOS,
    ARCTAN,

    SEC,
    CSC,
    COT
};

//TO IMPLEMENT
enum ROUNDING_FUNCS {
    FLOOR,
    CEIL,
    ROUND,
    TRUNC
};

//TO IMPLEMENT
enum OTHER_FUNCS {
    FACTORIAL,
    SQRT,
    ABS,
    SIGN
};

enum LOGARITHMIC_FUNCS {
    LOG,
    LOG_BASE,
    LOG_NATURAL
};

enum TRIG_FUNCS get_trig_func(const char *name);
enum LOGARITHMIC_FUNCS get_log_func(const char *name);

double evaluate_trig_func(double (*trig_func)(double), double argument);
bool is_trig_func(const char *name);

bool is_log_func(const char *name);
double evaluate_log_func(double (*log_func)(double), double argument);

#endif //CALCULATOR_H
