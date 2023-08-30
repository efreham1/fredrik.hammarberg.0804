extern char *strdup(const char *);

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;
typedef bool(*check_func)(char *);
typedef answer_t(*convert_func)(char *);


int read_string(char *buf, int buf_siz){
  int i = 0;
  int c;
  do{
    c = getchar();
    buf[i] = c;
    i++;
  }
  while(i<buf_siz-1 && c != '\n' && c != EOF);
  if (i>=buf_siz-1){
    buf[buf_siz-1]='\0';
    int b;
    do{
      b = getchar();
    }
    while (b != '\n');
  }
  else{
  buf[i-1] = '\0';
  }

  return i+1;
}

bool is_number(char *str){
    size_t len = strlen(str);
    int start = 0;
    if (str[0] == '-' && strlen(str) > 1){
        start = 1;
    }
    for (int i = start; i < len; i++){
        if (!isdigit(str[i])){
            return false;
        }
    }
    
    return true;
}

void print(char string[]){
    for (int i = 0; string[i] != '\0'; i++)
    {
        putchar(string[i]);
    } 
}

void println(char string[]){
    for (int i = 0; string[i] != '\0'; i++)
    {
        putchar(string[i]);
    }
    putchar('\n');
}

bool not_empty(char *str)
{
  return strlen(str) > 0;
}

answer_t ask_question(char *question, check_func check, convert_func convert){
    int buf_size = 255;
    char buf[buf_size];
    bool cond = false;
    while(!cond){
        print(question);
        read_string(buf, buf_size);
        cond = check(buf);
    }
    return convert(buf);
}

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.int_value;
}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).string_value;
}

bool is_shelf(char *str){
  if (!not_empty(str)) return false;
  char shelf_letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  int len_shelf_letters = 23;
  for (int i = 0; i <= len_shelf_letters; i++){
    if (i == len_shelf_letters) return false;
    if (shelf_letters[i] == str[0]) break;
  }
  return is_number(str+1);
  
}

char *ask_question_shelf(char *question){
  return ask_question(question, is_shelf, (convert_func) strdup).string_value;
}