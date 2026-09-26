#ifndef INPUTS_H
#define INPUTS_H

#include "option.h"

char* get_expression_string(EXPRESSION_TYPE type);

bool input_number_is_valid(int n);
int get_valid_option_number_input();

#endif //INPUTS_H
