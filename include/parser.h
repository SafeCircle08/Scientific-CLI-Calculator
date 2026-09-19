#ifndef PARSER_H
#define PARSER_H

extern const char *p;

bool char_is_number(void);
bool char_is(const char c);
void char_show(void);
void char_increment(void);
void char_skip_spaces(void);
bool char_is_alpha(void);

int char_to_int(void);

double factor(void);
double term(void);
double expression(void);

double sum(double a, double b);
double sub(double a, double b);
double prod(double a, double b);
double div(double a, double b);

#endif //PARSER_H