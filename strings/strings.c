
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *Remove spaces from a given string
 */

void removeSpaces(char* str) {

    int i,cnt=0;

    for(i=0; str[i]; i++){
	if(str[i]!=' '){
	    str[cnt] = str[i];
	    cnt++;
	}
    }
    str[cnt] = '\0';
}


/*
 *Check if a given sequence of moves for a robot is circular or not
 *http://www.geeksforgeeks.org/check-if-a-given-sequence-of-moves-for-a-robot-is-circular-or-not/
 */

struct dir {
    char L;
    char R;
} D[4] = {{'N', 's'}, {'S', 'N'}, {'W', 'E'}, {'E', 'W'}};

/*
 *D[0] = East
 *D[1] = West
 *D[2] = North
 *D[3] = South
 *
 *if u go East to Left , you end up North
 *if u go east to right , you end up south
 *if u go West to left , you end up left
 *
 *and so on ....
 *
 * 1. As the robot go we keep track of the directions( eg NSWS....). when the path is complete N cancelles out with S
 *and W cancells out with E. In other words, if the path is circular the XOR of path array should be 0.
 * 2. The valid circular path should always start with G
 * 3. The valid circular path should not have consequtive Ls or Rs.

 */

int checkCircularpath(char *path){

    int i,cnt=0;
    int sum=0;
    if(path[0]!='G')
	return 0;

    //check for consequitives Ls or Rs

    for(i=0;path[i];i++){
	if((path[i] == 'L' && path[i+1] == 'R') ||
	(path[i] == 'L' && path[i+1] == 'R')) {
	    return 0;
	}
    }

   //count the number of Gs as we need to initialize path array 
    for(i=0;path[i];i++){
	    cnt++;
    }

    int *P = (int*)malloc(sizeof(int)*cnt);
    P[0] = 'E';
    for(i=1;path[i];i++){
	
	switch(path[i]){
	    case 'L':
		if(P[i-1] == 'E')
		    P[i] = 'N';
		else if(P[i-1] == 'W')
		    P[i] = 'S';
		else if(P[i-1] == 'N')
		    P[i] = 'W';
		else if(P[i-1] == 'S')
		    P[i] = 'E';
		break;
			
	    case 'R':
		if(P[i-1] == 'E')
		    P[i] = 'S';
		else if(P[i-1] == 'W')
		    P[i] = 'N';
		else if(P[i-1] == 'N')
		    P[i] = 'E';
		else if(P[i-1] == 'S')
		    P[i] = 'W';
		break;

	    case 'G':
		P[i] = P[i-1];
		break;
	
	    default:
		return 0;
	}
    }

    for(i=0;P[i];i++){
	if(path[i] == 'G'){
	    printf("%c", P[i]);
	    if(P[i] == 'E')
		sum += 1;
	    else if (P[i] == 'W')
		sum -= 1;
	    else if (P[i] == 'N')
		sum += 1;
	    else if(P[i] == 'S') 
		sum -= 1;
	}
    }

    printf("\n");
    printf("sum : %d\n", sum);
    if(sum == 0)
	return 1;
    else 
	return 0;
}


void remove_dup_slashes( char *str) {

}


/*
 *void print_word_util(char **S, char *str, int n, int j) {
 *
 *
 *     int i;
 *
 *    if(j>n){
 *        return;
 *    }
 *
 *    str[j] =  S[i][j]; 
 *    printf("%s\n", str)
 *
 *        
 *
 *    for(j=0;j<n;j++){
 *        print_word_util(S, str, n, i, j++); 
 *
 *    }
 *
 *
 *
 *}
 */

void print_words(char *S) {

    /*int len;*/
    /*
     *len = strlen(S);
     */

    //create an array to store  the words
    /*char *str = (char*)malloc(sizeof(char) * (len+1));*/

    /*print_word_util(&S, str, len, i, j);*/




}


int regex_match(char* str, char *pat) {



return 0;
}


/*
 *string reduction problem
 *http://stackoverflow.com/questions/8551519/string-reduction-programming-contest-solution-needed/30156801#30156801


sol : 
1. put chars in a link list ( can use doubly link list)
2. p1 = start of list
3. p2 = p1->next;
4. while (all elements in list become same) {

	while(p2!=NUL){
		if(p1=>value != p2->value){
		p2 = p2->next;
		p2->value = replace with 3rd char
		del(p2);

		} else {
		p2 = p2->next;
		p1 = p1->next;
		}
	}
}

5. after the loop ends all chars will be same. get the lenth of link list
6. Reverse the orginal link list
8. run step 4 on reversed link list 
9. get the length on the list obtained in step 8
10 return the min len of step 5 and 9
 */

/*
 *Beautiful string problem
 *http://www.careercup.com/question?id=14463150
 *
 *Algo:
 *
 *For each i,
 *    - Decrement Cnt[S[i]] by 1.
 *    If S[i] is not in P: 
 *    - Append it to the P and remove all the characters in P that are smaller than S[i] and that have at least one occurence (using Cnt[]) in the substring i+1...n of S. 
 *    Else: 
 *    - Skip it.
 *
 *run this algo for example string :abcbeccdbacde
 *Cnt[] =  2 3 3 2 2 
 *         a b c d e
 *
 *Output(most beautiful string) : ecdba
 */

void palindrome() {

}

/*
 *http://www.careercup.com/question?id=5665972218232832
 */
//push char c in a stack(N) with stack pointer as sp
void push(char *N, char c, int *sp) {
    N[*sp] = c;
    *sp += 1;
}

//pop n elements from stack N , with stack pointer sp
void pop(char *N, int n, int *sp) {

    while(n>0){
	N[*sp] = '\0';
	n--;
	*sp -= 1;
    }
}

char* normalize(char *S) {

    int len, i=0;

    //stack pointer
    int sp = 0;
    char *N;
    len = strlen(S);
    if(len < 3)
	return NULL;
    //create space for normalized string
    N = (char*)calloc(sizeof(char), len+1);

    while(*S){
	//if you get a ".", check if the pattern is "../" or "./"
	if(S[i] == '.') {
	    if(strncmp(S, "./", 2) == 0){
		pop(N, 2, &sp); //pop last two chars 
		S = S+2;  //move 2 char fwd if the pattern is "./" 
	    } else if(strncmp(S, "../", 3) == 0){
		S = S+3; //move 3 chars fwd if pattern is "../"	
	    }
	} else {
	    push(N, S[i], &sp);
	    S++;
	}
    }

    return N;
}

int main() {
    /*char c;*/
    int choice;
    char str[] = "gee  ks f  or g  ee ks ";
    char path[128];
    /*do {*/

	printf("MENU OPTIONS\n");
	printf("1 -- remove spaces from string\n");
	printf("2-- Check if a given sequence of moves for a robot is circular or not\n");
	printf("3 -- Regex matching problem\n");
	printf("4 -- Palindrome detection with non-alphanumeric characters\n");
	printf("5 -- Normalize the path\n");
	
	

	printf("\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){
	    case 1:
		removeSpaces(str);
		printf("%s", str);
		break;

	    case 2:
		printf("Enter path\n");
		scanf("%s", path);
		printf("path is circular: %s", checkCircularpath(path)?"yes":"no");
		break;

	    case 4:
		palindrome();
		break;
		
	    case 5:
		printf("Enter path\n");
		fgets(path, 128, stdin);
		printf("Normalized path: %s\n", normalize(path));
		break;
		

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    /*}while((c=getchar())!='q'); */
    return 0;
}

