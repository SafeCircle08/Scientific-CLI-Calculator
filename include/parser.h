#ifndef PARSER_H
#define PARSER_H

#include "Node.h"

extern const char *p;

bool char_is_number(void);
bool char_is(const char c);
void char_show(void);
void char_increment(void);
void char_skip_spaces(void);
bool char_is_alpha(void);

int char_to_int(void);

Node* factor(void);
Node* term(void);
Node* expression(void);

double sum(double a, double b);
double sub(double a, double b);
double prod(double a, double b);
double div(double a, double b);

double evaluate_AST(Node* root);

#endif //PARSER_H