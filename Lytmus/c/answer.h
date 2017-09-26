/**
This file serves as the header file for your `answer.c` file. If you need
to declare new types, you can do so here.
*/

#ifndef _ANSWER_H_
#define _ANSWER_H_

#include <stdbool.h>


#define ROW_SIZE 1024
#define ARRAY_SIZE 1024
#define STRING_SIZE 1024
long schedule_with_lunch(char requests[ARRAY_SIZE][STRING_SIZE], int requests_size);
void print_schedules(char * requests[ARRAY_SIZE][STRING_SIZE], int requests_size);

#endif
