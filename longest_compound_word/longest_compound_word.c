#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "trie.h"
#include "utils.h"

int main(int argc, char*argv[]) {

    FILE *fp;
    char oword[WORD_SIZE];
    TNODE *root = NULL;
    QUEUE *q = NULL;

    if(argc != 2 || !argv[1])
	printf("Enter valid file name\n");

    fp = fopen(argv[1], "r");
    if(!fp){
	printf("Error opening file %s\n", argv[1]);
	exit(0);
    }

    /*initialize queue*/
    if(!(q = init_queue()))
	return 0;

    while(fscanf(fp,"%s",oword)!= EOF){

             /*printf("%s\n", oword);*/
	     /*add the words into the trie*/
             root = addWordInTrie(oword, root);
 
             build_queue(q, root, oword);

    }

    /*print_trie(root);*/
    /*print_queue(q);*/
    process_queue(q, root);

    fclose(fp); 
    return 0;
}
