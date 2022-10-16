#include <stdbool.h>

#pragma once

typedef union answer answer_t;

union answer
{
    int int_t;
    char *str_t;

};

typedef bool(*check_func)(char *);
typedef answer_t(*convert_func)(char *);

answer_t ask_question(char *question, check_func check, convert_func convert);

answer_t ask_question_string(char *question);

answer_t ask_question_int(char *question)

bool not_empty(char *str);

bool is_number(char *str);