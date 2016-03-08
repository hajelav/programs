#include "../utils.h"
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


void replace_spaces(char *str, char *pattern) {

    int non_space_count, result_len, pattern_len, space_count=0;
    int copy_from, copy_to, i=0;

    if(str[0]=='\0' || pattern[0]=='\0')
	return;

    pattern_len = strlen(pattern);

    /*first we count the spaces in the string*/

    while(str[i]!='\0') {

	if(str[i] == '-')
	    space_count++;
	 i++;
    }

    non_space_count = strlen(str) - space_count;
    
    /*length of the new string after replacing pattern*/
    result_len = space_count*pattern_len + non_space_count;

    copy_from = strlen(str)-1;
    copy_to = result_len-1;

    while(copy_from >= 0) {

	if(str[copy_from]!= '-') {
	    str[copy_to] = str[copy_from];
	    copy_to--;
	    copy_from--;
	} else {
	    strncpy(str+copy_to-pattern_len+1, pattern, pattern_len);
	    copy_from--;
	    copy_to = copy_to - pattern_len;
	}
    } 
}

/*
 *leetcode problem 76
 *Given a string S and a string T, find the minimum window(minimum substring) in S which will contain all the characters in T in complexity O(n).
 *
 *For example,
 *    S = "ADOBECODEBANC"
 *    T = "ABC"
 *    Minimum window is "BANC""
 *
 *    logic : http://www.geeksforgeeks.org/find-the-smallest-window-in-a-string-containing-all-characters-of-another-string/
 *    http://articles.leetcode.com/2010/11/finding-minimum-window-in-s-which.html
 */
    
char * min_window_substring(char *S, char *T) {

    int *needToFill; //hash of T. It stores the frequency of chars in T
    int *hasFound; // this store the frequency of chars in S, as we move along S
    int len_S, len_T;
    int start = 0, end = 0, i = 0;
    int count = 0; // maintain this var to count the number length of T in S 
    int min_window_start_idx = 0, min_window_end_idx = 0;
    int min_window = INT_MAX;
    if(!S || !T)
	return NULL;

    len_S = strlen(S);
    len_T = strlen(T);

    /*create a hash of 26 chars assuming that input is uppercase letters(this solution can be extended to generic case)*/
    needToFill = (int*)calloc(sizeof(int), 26); // this remains constant and used to keep the count of chars in T
    hasFound = (int*)calloc(sizeof(int), 26);  // this keeps changing as we move along S(char by char)

    /*go through T and fill the needToFill hash*/
    while(T[i]!='\0'){
	needToFill[T[i]-'a']++;
	i++;
    }

    /*now run through S*/
    while(end<len_S) {

	//if you found the char in T and the count of hasFound[char] is than needToFill[char]
	if(needToFill[S[end]-'a'])  {
	    if(hasFound[S[end]-'a'] < needToFill[S[end]-'a']){
		count++; //increment the count, which counts the total chars found in S matching T
	    }
	    hasFound[S[end]-'a']++; //increment the count in hasFound
	}

	//if we have found all the chars of T in S previously and we find first char of T again,then we move the start
	//pointer forward till the point the needToFill constrainst in maintained.
	if((min_window < INT_MAX) && (needToFill[S[start]-'a'] && S[end] == S[start]) && (count > 0)) {

	    while((needToFill[S[start]-'a'] == 0) || (hasFound[S[start]-'a'] > needToFill[S[start]-'a']))   {

		if(hasFound[S[start]-'a'] > needToFill[S[start]-'a'])
		    hasFound[S[start]-'a']--;
		start++;
	    }
	}
	/*when we have found the window containing all the chars in T, we calculate the indexes*/
	if(count == len_T){
	    if(end-start < min_window){
		min_window = end-start;
		min_window_start_idx = start;
		min_window_end_idx = end;
	    }
	} 

	end++;
    } //while ends

    /*if(min_window_start_idx>0 && min_window_end_idx>0) */
	printf("min window length : %d, [start index = %d end index = %d]\n", min_window+1, min_window_start_idx, min_window_end_idx);
    /*else*/
	/*printf("Min window length  : %d\n", min_window);*/

    return NULL;
    /***** HAS A BUG, NEED TO BE CORRECTED ** */
}


/*
 *leetcode problem 93
 *https://leetcode.com/problems/restore-ip-addresses/
 */
void restore_ip_address() {

    char str[128];
    int str_len;

    printf("Enter the string\n");
    scanf("%s", str);

    str_len = strlen(str);
     
    if(str_len < 4)
	return;

}

/*
 *leetcode problem 205
 *https://leetcode.com/problems/isomorphic-strings/
http://www.geeksforgeeks.org/check-if-two-given-strings-are-isomorphic-to-each-other/
*/

int isomorphic_strings(char *S, char *T) {

    /*define hash of 256 chars*/
    char hash[256];
    int i = 0;

    if(!S || !T || strlen(S)!=strlen(T))
	return 0;

    memset(hash, '\0', 256);

    while(S[i]){

	if(hash[S[i]-'a']!='\0' && hash[S[i]-'a']!=T[i])
	    return 0;
	else
	hash[S[i]-'a'] = T[i];
	i++;
    }
     return 1;
}

int is_valid_number(char *S) {
 
   int i, len, dot_count = 0;

   if(!S)
       return 0;

   len = strlen(S);
   for(i=0;i<len;i++){

       /*count the number of dots*/
       if(S[i] == '.')
	   dot_count++;

       /*
	*the string is not a number only if
	*    1. ascii value of any of the char (which is not '.' or '-') lies outside the range of '0' to '9'
	*    2. if we find a '-' sign other than the first index(ie '-' sign in between the srting) 
	*    3. if we find a '.' at the last postion of a string
	*    4. if we find more than one '.'
	*    5. if we find any space character
	*/

       if((S[i]!='.' && S[i]!='-' && (S[i]-'0' < 0 || S[i]-'0'> 9)) ||
	  (S[i] == '-' && i > 0)        ||
	  (S[i] == '.' && i == len-1) 	||
	  (dot_count > 1) ||
      	  (S[i] == ' ')){
	   return 0;
	  } 
   }
   return 1;
}

void reverse_string(char *S, int len) {
    int mid;
    char *begin, *end;
    char temp;

    //len = strlen(p);
    begin = S;
    end = S+len-1;
    mid = len/2;

    while(mid > 0) {
	//swap the chars
	temp = *begin;
	*begin = *end;
	*end = temp;

	begin++;
	end--;
	mid --;
    }
    printf("Reversed string : %s\n", S);

}

void reverse_words(char *p) {

    char *start,*rev;
    int count = 0;
    start = p;
    rev = p;

    while(*p!='\0'){
	if(*p!= ' ')
	    count ++;

	if(*(p+1) == ' ') {
	    reverse_string(start,count);
	    //printf("%s\n",start);
	    count =0;
	    start = p+2;
	}
	p++;
    }
    /*reverse the last word */
    reverse_string(start,count);

    /*once the individual words are reversed, reverse the sting again */
    reverse_string(rev,strlen(rev));
    printf("Reversed words : %s\n",rev);
}

  /*
   * linkedin
   *provide a method that takes two  words and returns the shortest distance (in words) between those two
   *words in the provided text. 
   *   Example:
   *     WordDistanceFinder finder = new WordDistanceFinder(Arrays.asList("the", "quick", "brown", "fox", "quick"));
   *     distance("fox","the") == 3;
   *     distance("quick", "fox") == 1;
   */
        
int shortest_distance(char **S, int len, char *str1, char *str2) {

    int i, dist1 = -1, dist2 = -1, dist = INT_MAX;

    if(!S || len <=0 || !str1 || !str2)
	return -1;

    for(i=0;i<len;i++){

	if(strcmp(S[i], str1)==0)
	    dist1 = i;
	else if(strcmp(S[i], str2)==0)
	    dist2 = i;

	if(dist1 >=0 && dist2 >=0 && MOD(dist1, dist2) < dist)
	    dist = MOD(dist1, dist2);
    }
    return (dist<INT_MAX?dist:-1);
}

int main() {
    /*char c;*/
    int choice;
    int n;
    char str[] = "gee  ks f  or g  ee ks ";
    char path[128];
    char S[128], T[128];
    char *pattern = "-20";
    char str1[32], str2[32];

    char **s;
    /*do {*/

	printf("MENU OPTIONS\n");
	printf("1 -- remove spaces from string\n");
	printf("2-- Check if a given sequence of moves for a robot is circular or not\n");
	printf("3 -- Regex matching problem\n");
	printf("4 -- Palindrome detection with non-alphanumeric characters\n");
	printf("5 -- Normalize the path\n");
	printf("6 -- replace space by percentage20 in a string\n");
	printf("7 -- minimum window substring\n");
	printf("8 -- integer to english words\n");
	printf("9 -- restore IP addresses\n");
	printf("10 -- check if strings are isomorphic\n");
	printf("11 -- function to determine if a string is a valid number without using any built-in function\n");
	printf("12 -- reverse string\n");
	printf("13 -- reverse words in a sentence\n");
	printf("14 -- shortest distance between words\n");
	printf("15 -- shortest distance between words\n");
	
	

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

	    case 6:
		memset(path, '\0', 128);
		printf("Enter string\n");
		scanf("%s", path);
		/*gets(path);*/
		replace_spaces(path, pattern);
		printf("%s\n", path);
		break;

	    case 7:

		printf("Enter the string\n");
		scanf("%s", S);
		printf("Enter the pattern\n");
		scanf("%s", T);

		min_window_substring(S, T);
		    break;

	    case 8:
		    /*interger_to_english_words();*/
		    break;

	    case 9:
		    restore_ip_address();
		    break;

	    case 10:
		    printf("Enter strings of equal length\n");
		    printf("Enter string 1\n");
		    scanf("%s", S);
		    printf("Enter string 2\n");
		    scanf("%s", T);
		    printf("Strings are isomorphic : %s\n", isomorphic_strings(S, T)?"Yes":"No");
		    break;

	    case 11:
		    printf("Enter the string\n");
		    scanf(" %[^\n]s", S); //reading a space through scanf
		    /*fgets(stdin, S, sizeof(S));*/
		    printf("Is number : %s\n", is_valid_number(S)?"yes":"no");
		    break;

	    case 12:
		    printf("Enter the string\n");
		    scanf("%s", S);
		    reverse_string(S, strlen(S));
		    break;
	    case 13:
		    printf("Enter the sentence\n");
		    scanf("%s", S);
		    /*fgets(S, 128, stdin);*/
		    reverse_words(S);
		    break;

	    case 14:
		    printf("Enter number of words\n");
		    scanf("%d", &n);
		    s = create_2Dchar_array(n, 128);
		    input_2Dchar_array(s, n, 128);

		    printf("enter word 1\n");
		    scanf("%s", str1);
		    printf("enter word 2\n");
		    scanf("%s", str2);
		    printf("Shortest distance between %s and %s : %d\n", str1, str2, shortest_distance(s, n, str1, str2));
		    break;





		    




	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    /*}while((c=getchar())!='q'); */
    return 0;
}

