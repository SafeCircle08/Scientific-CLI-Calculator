#include "calculator.h"
#include "math.h"
#include "string.h"
#include "parser.h"
#include "error.h"

const double e = 2.71828182845904523536;

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

double sum(double a, double b) { return (a + b); }
double sub(double a, double b) { return (a - b); }
double mul(double a, double b) { return (a * b); }
double divide(double a, double b) {
    if (b == 0.0) throw_division_by_zero_error();
    return (a / b);
}

double sec(double arg) { return (1 / cos(arg)); }
double csc(double arg) { return (1 / sin(arg)); }
double cot(double arg) { return (1 / tan(arg)); }

double log_base(double arg, double base) {
    if (arg <= 0) throw_invalid_argument_error();
    return (log(arg) / log(base));
}
double log10(double arg) { return log_base(arg, 10); }
double ln(double arg) { return log_base(arg, e);}

double root_n(double arg, double index) { return (pow(arg, 1.0 / index)); }
double sqrt(double arg) { return (pow(arg, 1.0 / 2.0)); }
double factorial(double arg) {
    if (arg < 0 || floor(arg) != arg) throw_invalid_argument_error();
    return tgamma(arg + 1);
}

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

bool is_root_func(const char *name) { return (strcmp(name, "root_") == 0); }
bool is_sqrt_func(const char *name) { return (strcmp(name, "sqrt") == 0); }

bool is_factorial_func(const char *name) { return (strcmp(name, "fact") == 0) || (*p == '!'); }

bool is_abs_func(const char *name) { return (strcmp(name, "abs") == 0) || (*p == '|'); }

bool is_sign_func(const char *name) { return (strcmp(name, "sign") == 0); }

double evaluate_log_func(double (*log_func)(double), double argument) {
    return log_func(argument);
}
double evaluate_trig_func(double (*trig_func)(double), double argument) {
    double result = 0;
    double radians = argument * M_PI / 180.0;
    result = trig_func(radians);
    return result;
}
double evaluate_root_func(double argument, double index) { return (pow(argument, 1.0 / index)); }

Node* expand_power(Node* node) {

    //x^3 -> x * x * x

    Node* result = copy_node(node->left);
    int exponent = (int)node->right->value;

    for (int i = 1; i < exponent; i++) {
        result = new_node_binary(
            NODE_MUL,
            result,
            copy_node(node->left)
        );
    }
    return result;
}
Node* expand_mul(Node* node) {
    if (node == NULL) return NULL;

    Node* left = node->left;
    Node* right = node->right;

    if (left->type == NODE_ADD) {
        //(A + B) * C = AC + BC

        Node* ac = new_node_binary(
            NODE_MUL,
            copy_node(left->left),
            copy_node(right)
        );

        Node* bc = new_node_binary(
            NODE_MUL,
            copy_node(left->right),
            copy_node(right)
        );

        return new_node_binary(
            NODE_ADD,
            ac, bc
        );
    }

    if (left->type == NODE_SUB) {
        //(A - B) * C = AC - BC
        Node* ac = new_node_binary(
           NODE_MUL,
           copy_node(left->left),
           copy_node(right)
       );

        Node* bc = new_node_binary(
            NODE_MUL,
            copy_node(left->right),
            copy_node(right)
        );

        return new_node_binary(
            NODE_SUB,
            ac, bc
        );
    }

    if (right->type == NODE_ADD) {
        //C * (A + B) = CA + CB
        Node* ca = new_node_binary(
            NODE_MUL,
            copy_node(left),
            copy_node(right->left)
        );

        Node* cb = new_node_binary(
            NODE_MUL,
            copy_node(left),
            copy_node(right->right)
        );

        return new_node_binary(
            NODE_ADD,
            ca, cb
        );
    }

    if (right->type == NODE_SUB) {
        //C * (A - B) = CA - CB
        Node* ca = new_node_binary(
            NODE_MUL,
            copy_node(left),
            copy_node(right->left)
        );

        Node* cb = new_node_binary(
            NODE_MUL,
            copy_node(left),
            copy_node(right->right)
        );

        return new_node_binary(
            NODE_SUB,
            ca, cb
        );
    }
    return node;
}
Node* expand(Node* node) {
    if (node == NULL) return NULL;

    if (node->type == NODE_POW) {
        Node* result = expand_power(node);
        if (result != node)
            return expand(result);
    }

    node->left = expand(node->left);
    node->right = expand(node->right);

    if (node->type == NODE_MUL) {
        Node* result = expand_mul(node);
        if (result != node)
            return expand(result);
    }
    return node;
}


Node* simplify(Node* node) {
    if (node == NULL) return NULL;


    node->left = simplify(node->left);
    node->right = simplify(node->right);

    if (node->type == NODE_MUL) {
        Node* left = node->left;
        Node* right = node->right;

        if (left->type == NODE_NUMBER && right->type == NODE_NUMBER) {
            return new_node_number(left->value * right->value);
        }

        if (left->type == NODE_NUMBER && left->value == 0)
            return new_node_number(0);
        if (right->type == NODE_NUMBER && right->value == 0)
            return new_node_number(0);

        if (left->type == NODE_NUMBER && left->value == 1)
            return right;
        if (right->type == NODE_NUMBER && right->value == 1)
            return left;
    }

    if (node->type == NODE_ADD) {
        Node* left = node->left;
        Node* right = node->right;
        if (left->type == NODE_NUMBER && right->type == NODE_NUMBER) {
            return new_node_number(left->value + right->value);
        }
        if (left->type == NODE_NUMBER && left->value == 0)
            return right;
        if (right->type == NODE_NUMBER && right->value == 0)
            return left;
    }

    if (node->type == NODE_SUB) {
        Node* left = node->left;
        Node* right = node->right;

        if (left->type == NODE_NUMBER && right->type == NODE_NUMBER)
            return new_node_number(left->value - right->value);

        if (right->type == NODE_NUMBER && right->value == 0)
            return left;
    }


    if (node->type == NODE_DIV) {
        Node* left = node->left;
        Node* right = node->right;

        if (right->type == NODE_NUMBER && right->value == 0)
            throw_division_by_zero_error();

        if (left->type == NODE_NUMBER && left->value == 0)
            return new_node_number(0);

        if (left->type == NODE_NUMBER && right->type == NODE_NUMBER)
            return new_node_number(left->value / right->value);

        if (right->type == NODE_NUMBER && right->value == 1)
            return left;
    }
    return node;
}




















