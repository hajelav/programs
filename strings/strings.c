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

/*
 *replace spaces by a pattern in a string
 */
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

/*
 *leetcode problem 65
 *https://leetcode.com/problems/valid-number/
 */

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

void print_string(char *S, int len){

    int i=0;
    if(!S || len<=0)
	return;

    while(i<len){
	printf("%c", S[i]);
	i++;
    }
}

void reverse_string(char *S, int len) {

    int i, j;
    char t;

    if(!S || len<=0)
	return;

    i = 0;
    j = len-1;

    while(i<j){
	t = S[i];
	S[i] = S[j];
	S[j] = t;     

	i++;
	j--;
    }
}

/*leetcode problem 186*/
void reverse_words(char *S) {

    int i, j, len;
    len = strlen(S);

    if(!S || len == 0)
	return;

    i = 0;
    j = 0;

    /*reverse the whole sentence first*/
    reverse_string(S, strlen(S));

    /*run the loop till the end of the sentence*/
    while(S[j]) {

	/*
	 *whenever we find a space, we reverse the word found previously , ie from i to j-1
	 *after we reverse the word  update i to point to next char after space   
	 */
	if(S[j] == ' '){
	    reverse_string(S+i, j-i);    			    
	    i = j+1;
	}
	j++;
    }

    /*reverse the last word*/
    if(j==len)
	reverse_string(S+i, j-i); 
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

/*
 *leetcode problem : 557
 *https://leetcode.com/problems/reverse-words-in-a-string-iii/#/description
 Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

 Example 1:

Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"

Note: In the string, each word is separated by single space and there will not be any extra space in the string. 
 */

void reverse_str(char *S , int low , int high) {

    char temp;

    if (!S || (low >= high))
	return;

    while(low < high) {
	temp = S[low];
	S[low] = S[high];
	S[high] = temp;

	low++;
	high--;
    }
}


void reverse_words_preserving_order(char *S) {

    int i, j, len;
    if (!S){
	printf("string is null");
	return;
    }

    i = 0;
    len = strlen(S);
    j = len - 1;
    i = j;

    while(j>0){

	if(i >= 0 && S[i] != ' '){
	    i--;
	} else {

	    reverse_str(S, i+1, j);
	    j = i-1;
	    i--;

	}
    }
}


/*
 *leetcode problem 468
 *validate ip4 address
 *Write a function to check whether an input string is a valid IPv4 address or IPv6 address or neither.
 *
 *IPv4 addresses are canonically represented in dot-decimal notation, which consists of four decimal numbers, each ranging from 0 to 255, separated by dots ("."), e.g.,172.16.254.1;
 *
 *Besides, leading zeros in the IPv4 is invalid. For example, the address 172.16.254.01 is invalid.
 */

int validate_ip_address(char *S) {

    int j, len, i;
    char *token;
    int dot_count = 0;

    /*
     *an ip address is valid only 
     *    1. No consequtive dots
     *    2. Should have exact 3 dots
     *    3. No dots in the front or end of string
     *    4. no leading zeros in any of the tokens( chars seperated by dots)
     *    5. Each token has to be between 0-255 ( including both 0 and 255)
     *    6. string should not be NULL
     *    7. token cannot be NULL
     *    8. if the length of token > 1, then no leading zeros and no consequitive 0s
     *
     */

    if (!S){
	printf("ip add is null");
	return 0;
    }

    len = strlen(S);

    if (S[0] == '.' || S[len-1] == '.'){
	printf("ip add has leading or trialing dots\n");
	return 0;
    }

    for(j=1;j<len-1;j++){
	if(S[j] == '.')
	    dot_count++;
	if(S[j] == '.' && S[j-1] == '.')
	    return 0;
    }

    if (dot_count!=3)
	return 0;

    /*tokenize the ip address validate each token*/
    token = strtok(S, ".");
    while( token != NULL ) 
    {
	printf("%s\n", (token));

	i = 0;
	while(token[i]!='\0'){
	    if(token[i]-'0' < 0 ||
		    token[i]-'0' > 255)
		return 0;
	i++;
	}
	if ( i < 1 || i > 3)
	    return 0;
	if(i >= 1 && token[0] == '0')
	    return 0;


	token = strtok(NULL, ".");
    }

    return 1;
}

/*
 *Run Length Encoding
 *Given an input string, write a function that returns the Run Length Encoded string for the input string.
 *
 *For example, if the input string is “wwwwaaadexxxxxx”, then the function should return “w4a3d1e1x6”.
 */

void run_length_encoding(char *S){

    int H[256]; // define hash to store all 255 chars
    char *result;
    int i, j, k, len, result_len=0;

    if (!S)
        return;
    len = strlen(S);

    if(len==1){
        printf("%c1\n", S[0]);
        return;
    }

    /*first pass: fill the hash */
    memset(H, 0, 256*sizeof(int));
    for(i=0;i<len;i++){

        H[(int)S[i]]++;
    }

    /*from the hash: find the length of result array*/
    for(i=0;i<256;i++){

        if(H[i]){
            result_len = result_len + 2;
        }
    }


    printf("result len:%d", result_len);
    
    result = create_1Dchar_array(result_len);

    k = 0;
    j = 1; //start iterating the array from index 1
    /*second pass: fill the result array which is run length encoded*/
    while(S[j] != '\0') {

       /*check if prev char is not as current char, then update the result array with char and freq */
        if(S[j] != S[j-1]) {
            result[k] = S[j-1];

            //convert int ( frequency) to char and update in result array
            result[k+1] = H[(int)S[j-1]]+'0';
            k = k+2;
        }
        j++;
    }

    result[k] = S[j-1];
    result[k+1] = H[(int)S[j-1]]+'0';

    printf("%s", result);
}


/*
 *Length of the longest substring without repeating characters
 *http://www.geeksforgeeks.org/length-of-the-longest-substring-without-repeating-characters/
 *
 *auxillary array to remember that we have visted the char and what was the index, when we last saw that char
 */
typedef struct hash {
    int visited;
    int index;
}hash;

int longest_substring_without_repeat_char(char *S) {


    int j = 1; // index to track the right end of the longest substring
    int i = 0; // index to track the left end of the longest substring
    int len; //len of string
    int max; //max length of substring without repeating characters

    struct hash H[26]; // delare the hash of 26 chars (assuming input String is all small case)

    for(i=0;i<26;i++){
        H[i].visited = 0;
        H[i].index = 0;
    };

    if (!S)
        return 0;

    len = strlen(S);
    if (len == 1)
        return 1;


    i =0;
    max = 1; // initially assign max length to be 1
    //fill the hash with the first char
    H[S[0]-'a'].visited = 1;
    H[S[0]-'a'].index = 0;

    /*iterate thru S: start from the 1st index*/
    while(j<len) {

        /*for each char check if we have not seen it(ie present in the hash)*/
        if(!H[S[j]-'a'].visited){

            if(j-i+1 > max){
                max = j-i+1;
                printf("left index: %d\n", i);
                printf("right index: %d\n", j);
            }

            /*update index of this char and mark as visited*/
            H[S[j]-'a'].visited = 1;

        }else{

            /*we have already visted the char before: check if the index lies betweeb i and j ?, if it does 
             * then update i to the next of index*/
            if (H[S[j]-'a'].index >= i)
                i = H[S[j]-'a'].index + 1;
            else
                printf("%d\n", i);

        }
        H[S[j]-'a'].index = j;

        j++;
    }

    return max;
}


int main() {
    /*char c;*/
    int choice;
    int n;
    char str[] = "gee  ks f  or g  ee ks ";
    char path[128];
    char S[250], T[128];
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
	printf("16 --  reverse the order of characters in each word within a sentence while still preserving whitespace and initial word\n");
	printf("17 -- validate ip address\n");
	printf("18 -- run length encoding\n");
	printf("19 -- longest substring without repeat character\n");
	
	

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
		    scanf(" %[^\n]s", S);  //make scanf work with spaces 
		    reverse_string(S, strlen(S));
		    print_string(S, strlen(S));
		    break;
	    case 13:
		    printf("Enter the sentence\n");
		    scanf(" %[^\n]s", S);  //make scanf work with spaces
		    /*fgets(S, 128, stdin);*/
		    reverse_words(S);
		    print_string(S, strlen(S));
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

		case 16:

		    printf("Enter the string\n");
		    scanf(" %[^\n]s", S);
		    reverse_words_preserving_order(S);
		    printf("%s", S);
		    break;

		case 17:
		    printf("Enter the ip address\n");
		    scanf(" %[^\n]s", S);
		    printf("IP address:%s", validate_ip_address(S)?"valid":"invalid");
		    break;

		case 18:
		    printf("Enter the string to be run length encoded\n");
		    scanf(" %s", S);
		    run_length_encoding(S);
		    break;
		case 19:
		    printf("Enter the string\n");
		    scanf(" %s", S);
		    printf("%d",longest_substring_without_repeat_char(S));
		    break;




	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    /*}while((c=getchar())!='q'); */
    return 0;
}

