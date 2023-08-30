#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int read_string(char *buf, int buf_siz);
bool is_number(char *str);
void print(char string[]);
void println(char string[]);
bool not_empty(char *str);
int ask_question_int(char *question);
char *ask_question_string(char *question);
bool is_shelf(char *str);
char *ask_question_shelf(char *question);

#ifndef __UTILS_H__
#define __UTILS_H__

#endif