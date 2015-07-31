/*
 *Trie implementation for strings(lowercase only)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 10

typedef struct NODE {
	struct TNODE *next;
	char c;
} NODE;

typedef struct TNODE {

     struct NODE node[NUM]; 
     char domain[256];
}TNODE;

TNODE *root = NULL;

void initTnode(TNODE* tnode) {
    int i;
    for(i=0;i<NUM;i++){

	tnode->node[i].next = NULL;
	tnode->node[i].c = '\0';
    }
    /*tnode->domain = NULL;*/
    memset(tnode->domain, 0, 256);
}

TNODE* createTrieNode() {

    TNODE *tnode;
	tnode = (TNODE*)malloc(sizeof(TNODE));
	if(tnode) {
	    initTnode(tnode);
	}
	return tnode?tnode:NULL;
}

void addWordInTrie(char *word, TNODE* trav, char* domain) {

    TNODE *temp;

    if(word == NULL || domain == NULL) {
	return;
    }

    if(trav == NULL) {
	trav = createTrieNode();
	root = trav;
    } 
	while(*word!='\0') {

	    if(trav->node[*word-'0'].next == NULL) {
		temp = createTrieNode();
	    temp->node[*word-'0'].c = *word;
		trav->node[*word-'0'].next = temp;
		trav = temp;
		if(*(word+1) == '\0'){
		    strncpy(trav->domain, domain, 256);
		}
		printf("node1=%c\n", trav->node[*word-'0'].c);
	    } else {
		trav = trav->node[*word-'0'].next;
		if(*(word+1) == '\0'){
		    strncpy(trav->domain, domain, 256);
		}
		printf("node2=%c\n", trav->node[*word-'0'].c);
	    }
	    word++;
	}
}

/*search for the word in the trie */
char*  searchWordInTrie(TNODE* troot, char *word) {

    if(troot==NULL || word == NULL) {
	return NULL;
    }

    while(*word!='\0') {

	if(troot->node[*word-'0'].next == NULL) {
	    return NULL;
	} 
	troot = troot->node[*word-'0'].next;
	printf("node=%c\n", troot->node[*word-'0'].c);
	word++;
    }
    return (troot->domain);
}

int main() {

    char c;
    char ip[256];
    char domain[256];
    int choice;
    TNODE *crawl;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Insert IP in Trie\n");
	printf("2 -- Search IP in Trie\n");

	printf("enter your choice\n");
	scanf("%d", &choice);

	switch(choice) {

	    case 1: 
		printf("Enter the IP(without dot)\n");
		scanf("%s", ip);
		printf("Enter the Domain Name\n");
		scanf("%s", domain);
		crawl = root;
		addWordInTrie(ip, crawl, domain);
		break;
	    case 2: 
		printf("Enter the string\n");
		scanf("%s", ip);
		char *d;
		crawl = root;
		d = searchWordInTrie(crawl, ip);
		printf("Domain: %s\n", d?d:"not found");
		break;
	}

    }while((c= getchar())!='q');

    return 0;
}
