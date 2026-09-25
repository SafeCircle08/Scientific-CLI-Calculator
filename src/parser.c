#include <stdio.h>
#include <string.h>
#include "math.h"
#include "parser.h"
#include "calculator.h"
#include "Node.h"
#include "error.h"

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
    /*
    double number = 0;

    if (char_is('(')) char_increment();

    number = expression();

    char_skip_spaces();
    if (char_is(')')) char_increment();
    return number;
    */
}

Node* evaluate_parentesis_AST() {
    Node* number = NULL;

    if (!char_is('(')) throw_parenthesis_error();
    char_increment();

    number = expression();

    char_skip_spaces();
    if (!char_is(')')) throw_parenthesis_error();

    char_increment();
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

Node* factor() {
    char_skip_spaces();
    char function_name[20];
    int i = 0;
    Node* node = NULL;

    if (char_is_alpha()) {
        while (char_is_alpha()) {
            function_name[i] = *p;
            i++;
            char_increment();
        }
        function_name[i] = '\0';

        if (strcmp(function_name, "e") == 0) node = new_node_number(e);
        else if (strcmp(function_name, "pi") == 0) node = new_node_number(M_PI);
        else if (is_trig_func(function_name)) {
            node = evaluate_parentesis_AST();

            if (strcmp(function_name, "sin") == 0) {
                node = new_node_unary(NODE_SIN, node);
            } else if (strcmp(function_name, "cos") == 0) {
                node = new_node_unary(NODE_COS, node);
            } else if (strcmp(function_name, "tan") == 0) {
                node = new_node_unary(NODE_TAN, node);
            }
        } else if (is_log_func(function_name)) {
            Node* node_base = NULL;
            char_show();
            if (strcmp(function_name, "log_") == 0) {
                if (char_is('(')) {
                    node_base = evaluate_parentesis_AST();
                }
                else node_base = new_node_number(collect_number());
            }

            node = evaluate_parentesis_AST();

            if (strcmp(function_name, "log") == 0) {
                node = new_node_unary(NODE_LOG, node);
            } else if (strcmp(function_name, "ln") == 0) {
                node = new_node_unary(NODE_LN, node);
            } else if (strcmp(function_name, "log_") == 0) {
                node = new_node_binary(NODE_LOG_BASE, node, node_base);
            }
        } else throw_invalid_function_error();
    }

    if (char_is_number() || char_is('.')) {
        node = new_node_number(collect_number());
    }

    if (char_is('(')) {
        node = evaluate_parentesis_AST();
    }

    if (char_is('!')) {
        char_increment();
        node = new_node_unary(NODE_FACTORIAL, node);
    }

    if (char_is('^')) {
        char_increment();

        Node* exponent;

        if (char_is('(')) exponent = evaluate_parentesis_AST();
        else exponent = new_node_number(collect_number());

        node = new_node_binary(NODE_POW, node, exponent);
    }
    return node;
}

Node* term() {
    char_skip_spaces();
    Node* term_node = factor();
    char_skip_spaces();

    while (char_is('*') || char_is('/')) {
        char operator = *p;
        char_increment();
        char_skip_spaces();

        Node* value = factor();
        if (operator == '*') term_node = new_node_binary(NODE_MUL, term_node, value);
        else if (operator == '/') term_node = new_node_binary(NODE_DIV, term_node, value);
        char_skip_spaces();
    }
    return term_node;
}

Node* expression() {
    char_skip_spaces();
    Node* result = term();
    char_skip_spaces();

    while (char_is('+') || char_is('-')) {
        char operator = *p;
        char_increment();
        char_skip_spaces();
        Node* value = term();
        if (operator == '+') result = new_node_binary(NODE_ADD, result, value);
        else if (operator == '-') result = new_node_binary(NODE_SUB, result, value);
        char_skip_spaces();
    }
    return result;
}

double evaluate_AST(Node* node) {
    if (node == NULL) return 0;

    switch (node->type) {
        case NODE_NUMBER: return node->value;
        case NODE_ADD: return evaluate_AST(node->left) + evaluate_AST(node->right);
        case NODE_SUB: return evaluate_AST(node->left) - evaluate_AST(node->right);
        case NODE_MUL: return evaluate_AST(node->left) * evaluate_AST(node->right);
        case NODE_DIV: return evaluate_AST(node->left) / evaluate_AST(node->right);

        case NODE_POW: return pow(
            evaluate_AST(node->left),
            evaluate_AST(node->right)
        );

        case NODE_FACTORIAL: return factorial(evaluate_AST(node->left));

        case NODE_SIN: return sin(evaluate_AST(node->left) * M_PI / 180.0);
        case NODE_COS: return cos(evaluate_AST(node->left) * M_PI / 180.0);
        case NODE_TAN: return tan(evaluate_AST(node->left) * M_PI / 180.0);

        case NODE_LOG: return log10(evaluate_AST(node->left));
        case NODE_LN: return ln(evaluate_AST(node->left));
        case NODE_LOG_BASE: return log_base(evaluate_AST(node->left), node->right->value);
    }
}