#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "Node.h"

extern const double e;

double sum(double a, double b);
double sub(double a, double b);
double mul(double a, double b);
double divide(double a, double b);

double sec(double arg);
double csc(double arg);
double cot(double arg);

double log10(double arg);
double log_base(double arg, double base);
double ln(double arg);

double root_n(double arg, double index);
double sqrt(double arg);
double factorial(double arg);

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

enum OTHER_FUNCS {
    FACTORIAL,
    ROOT,
    ABS, //to implement
    SIGN //to implement
};

enum LOGARITHMIC_FUNCS {
    LOG,
    LOG_BASE,
    LOG_NATURAL
};

enum TRIG_FUNCS get_trig_func(const char *name);
enum LOGARITHMIC_FUNCS get_log_func(const char *name);

bool is_root_func(const char *name);
bool is_sqrt_func(const char *name);
bool is_factorial_func(const char *name);
bool is_abs_func(const char *name);
bool is_sign_func(const char *name);

double evaluate_trig_func(double (*trig_func)(double), double argument);
bool is_trig_func(const char *name);

bool is_log_func(const char *name);
double evaluate_log_func(double (*log_func)(double), double argument);
double evaluate_root_func(double argument, double index);

Node* expand_power(Node* node);
Node* expand_mul(Node* node);

Node* simplify(Node* node);

Node* expand(Node* node);

#endif //CALCULATOR_H