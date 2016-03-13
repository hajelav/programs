#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "trie.h"

#define LINE_SIZE 256

int main(int argc, char*argv[]) {

    FILE *fp;
    char line[LINE_SIZE];
    char *token;
    TNODE *root = NULL;

    if(argc != 2 || !argv[1])
	printf("Enter valid file name\n");

    fp = fopen(argv[1], "r");

    if(!fp)
	exit(0);

    while(fgets(line, sizeof line, fp) != NULL) {
	token = strtok(line, "\r");
	while(token != NULL) {
	    /*printf("%s\n", token);*/
	    root = addWordInTrie(token, root);
	    token = strtok(NULL, "\n");
	}
    
    }

    print_trie(root);

    return 0;
}
