#include "general_TUI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void clear_input_buffer() {
	int c;
	do {
		c = getchar();
	}
	while (c != '\n' && c != EOF);
}


int read_string(char *buf, int buf_siz) {
	int c;
	int i = -1;

	do {
		if (i < buf_siz-1) { 
			i += 1;
		} else {
			buf[i] = '\0';
			clear_input_buffer();
			return i;
		}		
		c = getchar();
		buf[i] = c;
	}
	while (c != '\n');	
	buf[i] = '\0';
	return i;
}


bool not_empty(char *str) {
	return strlen(str) > 0;
}


bool is_number(char *str) {
	if (strlen(str) == 0) {
		return false;
	}
	for(int i = 0; i < strlen(str); ++i) {
		if (str[i] == 45 && strlen(str) > 1) {
			if (i !=0) {
				return false;
			}
		} else if (!isdigit(str[i])) {
			return false;
		}	
	}
	return true;
}

bool is_pos_number(char *str)
{
	if (strlen(str) == 0) {
		return false;
	}
	for(int i = 0; i < strlen(str); ++i) {
		if (str[i] == 45 && strlen(str) > 1) {
			if (i !=0) {
				return false;
			}
		} else if (!isdigit(str[i])) {
			return false;
		}	
	}
	if (atoi(str)< 0 )
	{
		return false;
	}
	
	return true;
}


answer_t ask_question(char *question, check_func check, convert_func convert) {
	int buf_siz = 255;
	char buf[buf_siz];
	printf("%s\n", question);
	read_string(buf, buf_siz);
	while (!check(buf))
	{
		printf("Answer does not have correct format.\n");
		printf("%s\n", question);
		read_string(buf, buf_siz);
	}
	return convert(buf);
}


int ask_question_int(char *question) {
	return ask_question(question, is_number, (convert_func) atoi).int_t;
}

char *ask_question_string(char *question) {
	return ask_question(question, not_empty, (convert_func) strdup).str_t;
}

int ask_question_u_int(char *question)	{
	return ask_question(question, is_pos_number, (convert_func) atoi).int_t;
}