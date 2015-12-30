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

char* count_alphabet(char *P, int *input) {

    int hash[256];
    char *alphabet = NULL;
    int i, pat_len, count = 0;

    if(!P)
	return NULL;

    memset(hash, 0, sizeof(hash));

    pat_len = strlen(P);

    //run the loop through the pattern
    for(i=0;i<pat_len;i++){
	if(!hash[P[i]-'a']){
	    hash[P[i]-'a']++;
	    count++;
	}
    }

    //Now we have the count of the number of distinctive alphabets in the pattern, we create an array of distintive alphabets
    alphabet = create_1Dchar_array(count);
    if(!alphabet)
	return NULL;

    //store the count before resetting it
    *input = count;
    count = 0;

    //reset the hash array again
    memset(hash, 0, sizeof(hash));


    //run through the pattern again to fill in the alphabet array
    for(i=0;i<pat_len;i++){
	if(!hash[P[i]-'a']){
	    alphabet[count] =  P[i];
	    hash[P[i]-'a']++;
	    count++;
	}
    }
    return alphabet;
}

/*refer to string matching algo using finite automata in Coreman*/
char* delta(char *pat, int state, char alphabet) {

    char *P = NULL;
    if(state == 0){
	/*
	 *if its 0th state, then P will be just the concatination of P0(NULL) and alphabet for eg:
	 *delta(0, a) = P0.a = a
	 *delta(0, b) = P0.b = b
	 */
	P = create_1Dchar_array(1);
	P[0] = alphabet;
    } else {
	/*
	 *if its not the 0th state, then create an array of state len + 1 (for concatinating the alphabet)
	 */
	P = create_1Dchar_array(state+1);

	//copy state number of chars from pattern to P array
	memcpy(P, pat, state);

	//concatinate the alphabet to P
	P[state] = alphabet;
    }
    return P;
}

int longest_common_prefix(char *pat, char *P) {

    int count = 0;
    int high_pat = 0; //points to the start of pattern
    int low_P;


    low_P = strlen(P)-1; //points to the end of P

    if(P[low_P] == pat[high_pat])
	count++;

    high_pat++;
    low_P--;

    /*run the loop from the end of P, and compare P from the start of pattern, if we get a match then store the count as the current value of the high pointer.*/
    while(low_P >= 0) {

	if(memcmp(pat, P+low_P, high_pat+1) == 0){
	    count = high_pat+1;
	}

	low_P--;
	high_pat++;
    }
    return count;
}

int string_matching_finite_automata(char *text, char *pat) {

    int input_alphabet = 0; // count of distinct input alphabets in pattern(pat)
    int state; //no of states in the finite automation state machine
    char *alphabet; //array to store distinct alphabets in pattern array 
    int **table; // table to store the state transitions of finite automation machine
    char *P;
    int i, j;

    //first we need to count the number of different chars in the pattern(input). This will be used to create the finite automation state machine
    alphabet = count_alphabet(pat, &input_alphabet);
    printf("Input alphabet : %d, hash : %s\n", input_alphabet, alphabet);

    //no of states is always 1 more than the length of the pattern
    state = strlen(pat)+1;

    //create a table for the finite automation state machine
    table =  create_2Darray(state, input_alphabet);

    for(i=0;i<state;i++){
	for(j=0;j<input_alphabet;j++){
	    P = delta(pat, i, alphabet[j]);
	    printf("delta(%d, %c) = %s\n", i, alphabet[j], P);
	    /*Now we need to find out the longest prefix of pattern(pat) that is also a suffix of P*/
	    table[i][j] = longest_common_prefix(pat, P);
	}
    }
    print_2Darray(table, state, input_alphabet);
    return 0;
}

int main() {

    char c;
    int choice;
    char T[128], P[32];

    do {
	printf("MENU OPTIONS\n");
	printf("1 -- naive string matching algorithm\n");
	printf("2 -- string matching with finite automata\n");
	
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
	    case 2: 
		printf("Enter the text string\n");
		scanf("%s", T);
		printf("Enter the pattern string\n");
		scanf("%s", P);
		printf("Pattern found at index : %d\n", string_matching_finite_automata(T, P));
		break;

	    default:
		printf("Invalid option\n");
		break;
	}

    }while((c= getchar())!='q');

    return 0;
}
