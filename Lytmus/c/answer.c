/**
Write your solution in this file.

You can build, execute, and test your answer either by pressing 'Try Answer'
in the side panel, or by running the following commands on the command line:

To build your answer:
    make
To run the previously built executable:
    ./answer <test_case_path>
For example:
    ./answer inputs/large_input.json

You can organize your code as you wish (eg, use auxiliary files) as long as
the binary `answer` produces the expected output.
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "answer.h"


/**
 * Implement your solution here.
 *
 * @param requests List of appointment requests
 * @param requests_size The number of elements in the array.
 * @return Total duration of the accepted requests that maximizes the amount of time that Heather works.
 */
long schedule_with_lunch(char requests[ARRAY_SIZE][STRING_SIZE], int requests_size)
{

    print_schedules(requests, requests_size);
    return -1;
}


void print_schedules(char * requests[ARRAY_SIZE][STRING_SIZE], int requests_size) {

    int i;
    for(i=0; i < requests_size; i++){
     printf("%s\n", requests[i]);
    }



}
