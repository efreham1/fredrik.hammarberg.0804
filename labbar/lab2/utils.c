#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


int ask_question_int(char *question){

  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", question);
      conversions = scanf("%d", &result);
      int c;
      do
        {
          c = getchar();
        }
      while (c != '\n' && c != EOF);
      putchar('\n');
    }
  while (conversions < 1);
  return result;
}

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

char *ask_question_string(char *question, char *buf, int buf_siz){
  char *result = "";
  do{
    printf("%s", question);
    read_string(buf, buf_siz);
    result = buf;
  }
  while(result == "");
  return result;
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