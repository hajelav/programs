/**
 * Run your answer against a specific test-case input from a JSON file.
 *
 * This file serves two purposes:
 *
 *     * It's a convenience script that allows you to execute your answer with
 *       a test-case, and view the results in the generated `output.json` file
 *       or stdout. It's analogous to pressing 'Try Answer' on the side panel,
 *       except it doesn't tell you if your answer is right or wrong.
 *
 *     * It's used by the Lytmus platform to execute your answer with private
 *       test-cases.
 *
 * You can build, execute, and test your answer either by pressing 'Try Answer'
 * in the side panel, or by running the following commands on the command line:
 *
 * To build your answer:
 *      make
 * To run the previously built executable:
 *      ./answer <test_case_path>
 * For example:
        ./answer inputs/large_input.json
 * ----------------------------------------------------------------------------
 *    IMPORTANT: You DO NOT need to modify this file. If you decide to do so,
 *               please follow these guidelines:
 *
 *    1. Update the Makefile if you add new files or rename existing ones. DO
 *       NOT rename the `Makefile`
 *
 *    2. This file must always accept as a first argument the path to the
 *       JSON-encoded test file.
 *
 *    3. This file must always write to a file called `output.json`, located
 *       in the same folder as `test_answer.c`.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "answer.h"
#include "lytmus_json.h"

// Output file name. DO NOT change it
#define OUTPUT_FILENAME "output.json"


/**
 * Print JSON element to a string
 **/
char *print_element(cJSON *json, const char *name) {

    return cJSON_Print(cJSON_GetObjectItem(json, name));
}

/**
 * Helper to read JSON array of strings into a C array
 */
void read_string_list(cJSON *json, char output[ARRAY_SIZE][STRING_SIZE],
                      int *size) {

    int i;
    for (i = 0; i < cJSON_GetArraySize(json); i++)
    {

        cJSON *subitem = cJSON_GetArrayItem(json, i);
        strcpy(output[i], subitem->valuestring);
    }
    *size = i;
}

int main(int argc, char *argv[])
{
    char *filename = NULL;
    cJSON *json = NULL;
    cJSON *output_json = NULL;

    if (argc != 2) {
        fprintf(stderr, "Error, the name of the input file must be provided as"
            " a command line argument.\n");
        exit(1);
    }

    filename = argv[1];

    json = read_json(filename);

    if (json == NULL) {
        fprintf(stderr, "Error parsing json file\n");
        return 1;
    }

    // Validate input parameter types
    validate_parameter(json, cJSON_Array, "requests", "array of strings");

    // Assign input parameters to local variables
    
    int requests_size = 0;
    char *requests_mem = malloc(ARRAY_SIZE * STRING_SIZE);
    char (*requests)[STRING_SIZE] = (char(*)[STRING_SIZE])&requests_mem[0];
    cJSON *requests_json = cJSON_GetObjectItem(json, "requests");
    read_string_list(requests_json, requests, &requests_size);


    printf("Calling schedule_with_lunch()\n");
    printf("requests=%s, requests_size=%d\n", print_element(json, "requests"), requests_size);

    // run your answer with the desired test-case
    long output_object = schedule_with_lunch(requests, requests_size);

    output_json = cJSON_CreateNumber(output_object);

    printf("Returned: %s", cJSON_Print(output_json));

    // Write results to the output.json file
    write_json(output_json, OUTPUT_FILENAME);

    cJSON_Delete(output_json);

    return 0;
}
