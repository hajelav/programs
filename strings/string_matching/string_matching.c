#include "../../utils.h"

int naive_string_matching(char *text, char *pat) {

    int text_len, pat_len;
    int i, res = -1;
    //if string or pattern is a null or empty string
    if(!text || !pat)
	return res;

    text_len = strlen(text);
    pat_len = strlen(pat);

    for(i=0;i<(text_len-pat_len+1);i++){
	if(memcmp(pat, text+i, pat_len)==0) {
	    res = i;
	    break;
	}
    }
    return res; 
}



int main() {

    char c;
    int choice;
    char T[128], P[32];

    do {
	printf("MENU OPTIONS\n");
	printf("1 -- naive string matching algorithm\n");
	
	printf("enter your choice\n");
	scanf("%d", &choice);

	switch(choice) {

	    case 1: 
		printf("Enter the text string\n");
		scanf("%s", T);
		printf("Enter the pattern string\n");
		scanf("%s", P);
		printf("Pattern found at index : %d\n", naive_string_matching(T, P));
		break;

	    default:
		printf("Invalid option\n");
		break;
	}

    }while((c= getchar())!='q');

    return 0;
}
