#include <stdbool.h>
#include <stdbool.h>

#pragma once

typedef union answer answer_t;

union answer
{
    int int_t;
    char *str_t;

};

typedef bool(*check_func)(char * str, void *extra);
typedef answer_t(*convert_func)(char *str, void *extra);

answer_t ask_question(char *question, check_func check, void *check_extra, convert_func convert, void *convert_extra);

char *ask_question_string(char *question);

int ask_question_int(char *question);

bool not_empty(char *str);

bool is_number(char *str);

int ask_question_u_int(char *question);

answer_t str_to_int(char *str, void *extra);

answer_t str_to_str(char *str, void *extra);