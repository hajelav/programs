/**
 * @file longest_compound_word.c
 * @brief To calculate the longest/second longest concatinated word from a given text file
 * @author Vivek Hajela
 * @version 1.0
 * @date 2016-03-14
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "trie.h"
#include "utils.h"

int main(int argc, char*argv[]) {

    FILE *fp;
    char oword[WORD_SIZE];
    /*char *max_word = NULL, *sec_max_word = NULL;*/
    TNODE *root = NULL;
    QUEUE *q = NULL;
    HASH *h = NULL;

    if(argc != 2 || !argv[1])
	printf("Enter valid file name\n");

    fp = fopen(argv[1], "r");

    if(!fp){
	printf("Error opening file %s\n", argv[1]);
	exit(0);
    }

    /*initialize queue*/
    if(!(q = init_queue())){
	printf("failed to initilize queue\n");
	return 0;
    }

    /*initialize hash*/
    if(!(h = hash_init())){
	printf("failed to initilize hash\n");
	return 0;
    }

    /*parse input file*/
    while(fscanf(fp,"%s",oword)!= EOF){

	/*add the words into the trie*/
	root = addWordInTrie(oword, root);

	/*build the queue of original + suffix pairs*/
	build_queue(q, root, oword);
    }

    /*print_trie(root);*/
    print_queue(q);
    /*process_queue(q, root, h);*/
    /*hash_print(h);*/

/*
 *    max_word = get_max_word(h);
 *    sec_max_word = get_sec_max_word(h);
 *
 *    printf("Longest concatinated word : %s[len:%zu]\n", max_word, strlen(max_word));
 *    printf("Second longest concatinated word : %s[len:%zu]\n", sec_max_word, strlen(sec_max_word));
 *    printf("Total word count: %d\n", h->total_word_count);
 *
 *    [>free the memory<]
 *    hash_destroy(&h);
 *    trie_destroy(&root);
 */
    /*queue_destroy(&q);*/

    fclose(fp); 
    return 0;
}
