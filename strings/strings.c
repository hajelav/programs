#include "../utils.h"


/*
 *reverse string
 *Write a function that takes a string as input and returns the string reversed.
 *
 *Example:
 *Given s = "hello", return "olleh".
 *
 */

char* reverseString(char* S) {


    int i, j, len;
    char t;

    if(!S)
        return NULL;

    len = strlen(S);
    if(len <= 0)
        return "";

    i = 0;
    j = len-1;

    while(i<j){
        t = S[i];
        S[i] = S[j];
        S[j] = t;     

        i++;
        j--;
    }

    return S;

}

/*
 *reverse words in a string - preserving whitespace and initial word order 
 *Given a string, you need to reverse the order of characters in each word within a sentence while still preserving    whitespace and initial word order.
 *
 *Example 1:
 *Input: "Let's take LeetCode contest"
 *Output: "s'teL ekat edoCteeL tsetnoc"
 */

void reverseStr(char *S , int low , int high) {

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

char* reverseWordsPreservingOrder(char* s) {

    int len;
    int i, j;
    if(!s)
        return NULL;
    len = strlen(s);

    if(len <= 0)
        return "";

    i = j = 0;
    while(j < len){

        if(j+1<len && (s[j] != ' ') && (s[j+1] == ' ')) {

            reverseStr(s, i, j);
            i = j+1;

        } else if(s[j] == ' '){
            i++;
        }
        j++;
    }
    reverseStr(s, i, len-1);

    return s;

}

/*
 *reverse words in a string  : string contains single spaces only
 *Given an input string , reverse the string word by word. 
 *
 *Example:
 *
 *Input:  ["t","h","e"," ","s","k","y"," ","i","s"," ","b","l","u","e"]
 *Output: ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]
 *Note: 
 *
 *A word is defined as a sequence of non-space characters.
 *The input string does not contain leading or trailing spaces.
 *The words are always separated by a single space.
 *
 */
void reverseWordsSingleSpace(char *S) {

    int i, j, len;
    len = strlen(S);

    if(!S || len == 0)
        return;

    i = 0;
    j = 0;

    /*reverse the whole sentence first*/
    reverseStr(S, i, len-1);

    /*run the loop till the end of the sentence*/
    while(S[j]) {

        /*
         *whenever we find a space, we reverse the word found previously , ie from i to j-1
         *after we reverse the word  update i to point to next char after space   
         */
        if(S[j] == ' '){
            reverseStr(S, i, j-1);    			    
            i = j+1;
        }
        j++;
    }

    /*reverse the last word*/
    if(j==len)
        reverseStr(S, i, j-1); 
    /*printf("%s", S);*/
}


/*
 *reverse words in a string : a string can contain multiple spaces
 *                    
 *Example:  
 *
 *Input: "the sky is blue",
 *    Output: "blue is sky the".
 *    Note:
 *
 *    - A word is defined as a sequence of non-space characters.
 *    - Input string may contain leading or trailing spaces. However, your reversed string should not contain leading or      trailing spaces.
 *    - You need to reduce multiple spaces between two words to a single space in the reversed string.
 */


void reverseWordsMultipleSpaces(char *S) {

    int i, j, len;
    len = strlen(S);

    if(!S || len == 0)
        return;

    /*
     *This piece of code remove all leading/tracing spaces,
     *and reduce spaces between words to just one space
     START
     */

    i = 0;
    j = 0;

    while(S[j]) {

        if(j-1 >= 0 && S[j] == ' ' && S[j-1] != ' ') {
     //       S[i] = ' ';
            i++; j++;

        } else if(S[j] != ' ') {

            S[i] = S[j];
            i++; j++;

        } else {
            j++;
        }

    } 

    S[i] = '\0';

    /*if the last element is space , then make it null // test case passes in leetcode*/
    if(i-1 >=0 && S[i-1] == ' ')
        S[i-1] = '\0';

    /*
     *This piece of code remove all leading/tracing spaces,
     *and reduce spaces between words to just one space
     END
     */
    

    /*now reverse the words in the sentence*/
    reverseWordsSingleSpace(S);
    printf("%s", S);


}
/*
 *valid palindrome
 *
 *Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
 *
 *Note: For the purpose of this problem, we define empty string as valid palindrome.
 *
 *Example 1:
 *
 *Input: "A man, a plan, a canal: Panama"
 *Output: true
 *Example 2:
 *
 *Input: "race a car"
 *Output: false
 */

bool isValid(char c) {

    if((c >= 'A' && c <= 'Z') || 
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9'))

        return true;
    return false;

}

bool isPalindrome(char* s) {

    int len;
    int i, j;

    if(!s)
        return false;
    len = strlen(s);

    if(len <=0)
        return true;

    i=0; j=len-1;

    while(i<j){

        if( isValid(s[i]) && isValid(s[j])){

            if( toupper(s[i]) != toupper(s[j]) )
                return false;
            i++; j--;

        } else if( !isValid(s[i]) && isValid(s[j]) ){
            i++;
        } else if( isValid(s[i]) && !isValid(s[j]) ){
            j--;
        } else {
            i++; j--;
        }

    }

    return true;
}

/*
 *read n characters given read4 - call read only once per test case

 *The API: int read4(char *buf) reads 4 characters at a time from a file.
 *
 *The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.
 *
 *By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.
 *
 *Example 1:
 *
 *Input: buf = "abc", n = 4
 *Output: "abc"
 *Explanation: The actual number of characters read is 3, which is "abc".
 *Example 2:
 *
 *Input: buf = "abcde", n = 5 
 *Output: "abcde"
 *Note:
 *The read function will only be called once for each test case.
 */

int read4(char* buf){
/*implemented by called*/
    return 0;
}

int read(char *buf, int n) {


    char *buf4 = (char*)malloc(sizeof(char)*4);
    int bytesRead = 0;
    int totalBytesRead = 0;

    if(!buf || (*buf == '\0') || n<=0)
        return 0;



    while(n > 0) {

        bytesRead = read4(buf4);

        if(bytesRead < 0)
            return 0;
        if(bytesRead == 0)
            break;

        
        bytesRead  = MIN(bytesRead, n);

        strncpy(buf+totalBytesRead, buf4, bytesRead);
        totalBytesRead += bytesRead;
        n -= bytesRead;

    } 
    return totalBytesRead;
} 

/*
 *implement strstr().
 *
 *Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
 *
 *Example 1:
 *
 *Input: haystack = "hello", needle = "ll"
 *Output: 2
 *Example 2:
 *
 *Input: haystack = "aaaaa", needle = "bba"
 *Output: -1
 *Clarification:
 *
 *What should we return when needle is an empty string? This is a great question to ask during an interview.
 *
 *For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().
 */

int strStr(char* haystack, char* needle) {

    int i, lenNeedle, lenHaystack;
    if(!haystack || !needle)
        return 0;
    lenNeedle = strlen(needle);
    lenHaystack = strlen(haystack);

    if(lenNeedle > lenHaystack)
        return -1;

    for(i=0; i<(lenHaystack-lenNeedle+1); i++){

        if(memcmp(haystack+i, needle, lenNeedle) == 0)
            return i;
    }

    return -1;
}

/*
 *valid parentheses
 *
 *Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 *
 *An input string is valid if:
 *
 *Open brackets must be closed by the same type of brackets.
 *Open brackets must be closed in the correct order.
 *Note that an empty string is also considered valid.
 *
 *Example 1:
 *
 *Input: "()"
 *Output: true
 *Example 2:
 *
 *Input: "()[]{}"
 *Output: true
 *Example 3:
 *
 *Input: "(]"
 *Output: false
 */

bool isValidParentheses(char* s) {

    int i = 0, len, stackPtr = -1;
    char *stack;

    if(!s)
        return false;

    len = strlen(s);

    if(len <= 0)
        return true;

    /*create a stack of size len+1*/
    stack = (char*)calloc(len+1, sizeof(char));
    stack[len] = '\0';

    while(i < len) {

        if( (s[i] == '(') ||
                (s[i] == '{') ||
                (s[i] == '[') ) {

            /*increment stack pointer and push into the stack*/
            stack[++stackPtr] = s[i];


        } else  if( (stackPtr >= 0 && s[i] == ')' && stack[stackPtr] == '(') ||
                (stackPtr >= 0 && s[i] == '}' && stack[stackPtr] == '{') ||
                (stackPtr >= 0 && s[i] == ']' && stack[stackPtr] == '[') ) {

            /*pop the stack and decrement stack pointer*/
                    stack[stackPtr--] = '\0';
        } else 
            return false;

        i++;

    }

    free(stack);
    /*return true if stack is empty*/
    if(stackPtr < 0)
        return true;

    return false;
}

/*
 *add binary strings
 *
 *Given two binary strings, return their sum (also a binary string).
 *
 *The input strings are both non-empty and contains only characters 1 or 0.
 *
 *Example 1:
 *
 *Input: a = "11", b = "1"
 *Output: "100"
 *Example 2:
 *
 *Input: a = "1010", b = "1011"
 *Output: "10101"
 */

void reverse(char *A){

    int len, low = 0, high, temp;
    len = strlen(A);

    if(len == 0)
        return;

    high = len-1;
    while(low < high){

        temp = A[low];
        A[low] = A[high];
        A[high] = temp;

        low++; high--;
    }

}

char* addBinary(char* A, char* B) {

    int len, lenA, lenB, count=0;
    int C = 0;

    int i=0, j=0, tempA,tempB;
    char *sum;

    if(!A || !B)
        return NULL;

    lenA = strlen(A);
    lenB = strlen(B);

    if(lenA == 0 || lenB == 0)
        return NULL;

    /*get the max len of the two strings*/
    len = MAX(lenA, lenB);

    /*
     *create a new array to store the result. the length of new array
     *will max (lenA, lenB) + 1(to store the carry, if carry > 0) + 1(to store the last '\0' char)
     */

    sum = (char*)calloc(len+2, sizeof(char));
    sum[len+1] = '\0';

    /*reverse both the binary arrays, since the addition is done from LSB in the original arrays*/
    reverse(A);
    reverse(B);


    /*run the loop til both the arrays are iterated*/
    while((i<lenA) || (j<lenB)) {

        if(i<lenA)
            tempA = A[i]-'0';
        else
            tempA = 0;

        if(j<lenB)
            tempB = B[j]-'0';
        else
            tempB = 0;

        if(tempA + tempB + C == 0){
            sum[count] = '0'; C = 0;
        } else if(tempA + tempB + C == 1){
            sum[count] = '1'; C = 0;
        }else if(tempA + tempB + C == 2){
            sum[count] = '0'; C = 1;
        } else if(tempA + tempB + C == 3){
            sum[count] = '1'; C = 1;
        }

        count++; i++; j++;

    }


    /*if the carry > 0, add 1 to the sum array*/
    if(C>0)
        sum[count] = '1';


    /*reverse the result to get the right sum*/
    reverse(sum);
    return sum;
}

/*
 *
 *string to integer (atoi)
 *
 *Implement atoi which converts a string to an integer.
 *
 *The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.
 *
 *The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.
 *
 *If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.
 *
 *If no valid conversion could be performed, a zero value is returned.
 *
 *Note:
 *
 *Only the space character ' ' is considered as whitespace character.
 *Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.
 *Example 1:
 *
 *Input: "42"
 *Output: 42
 *Example 2:
 *
 *Input: "   -42"
 *Output: -42
 *Explanation: The first non-whitespace character is '-', which is the minus sign.
 *             Then take as many numerical digits as possible, which gets 42.
 *             Example 3:
 *
 *             Input: "4193 with words"
 *             Output: 4193
 *             Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.
 *             Example 4:
 *
 *             Input: "words and 987"
 *             Output: 0
 *             Explanation: The first non-whitespace character is 'w', which is not a numerical 
 *                          digit or a +/- sign. Therefore no valid conversion could be performed.
 *                          Example 5:
 *
 *            Input: "-91283472332"
 *            Output: -2147483648
 *            Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
 *                         Thefore INT_MIN (−231) is returned.
 *
 *
 */
int myAtoi(char* str) {

    char *strp = str;

    while(*strp&&*strp==' ')
        strp++;

    int ret = 0;
    int ret_pre = 0;
    int sign = 1;

    if(*strp=='+'||*strp=='-')
    {
        if(*strp=='-')
            sign = -1;
        strp++;
    }

    if(*strp<'0'||*strp>'9')
        return 0;
    else
    {
        while(*strp>='0'&&*strp<='9')
        {
            ret = ret*10 + *strp - '0';
            if(ret/10!=ret_pre)
                return (sign<0) ? INT_MIN : INT_MAX;
            else
            {
                ret_pre = ret;
                strp++;
            }
        }
        ret = ret * sign;

        return (ret<INT_MAX && ret>INT_MIN) ? ret : ((ret > 0) ? INT_MAX : INT_MIN);
    }
}



/*
 *remove spaces from a given string
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

/*
 *struct dir {
 *    char L;
 *    char R;
 *} D[4] = {{'N', 's'}, {'S', 'N'}, {'W', 'E'}, {'E', 'W'}};
 */

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

/*
 *Given an absolute path for a file (Unix-style), simplify it.
 *
 *For example,
 *    path = "/home/", => "/home"
 *    path = "/a/./b/../../c/", => "/c"
 *
 *    logic :
 *
 *    while(each char in path){
 *
 *      if(char != "."){
 *
 *      if(stack->top == '\' and char == '\')
 *          continue;
 *      
 *      push(stack, char);
 *
 *      } else {
 *          pop(Stack);
 *      }
 *
 *    }//while ends
 */

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
 *
 *    define a hash which will keep track 1) if we have seen a char in S, and 2) last seen index of char
 *    we will fill the hash with hash with chars of T ( and not the index part )
 *    Now we will start reading S char by char , and see if that char is present in hash, if yes then we update 
 *    the last seen index  for that char. As we fill the hash, we will also keep track of the number of chars covered so far
 *    When the last seen indices of all the chars are covered in the hash, then the difference of the min and max index is
 *    the window. We have to find min of such window
 */


/*define a custom hash which will keep track of the chars of T seen in S, and their corresponding indices*/
typedef struct _hash{
    int H[256];
    int lastSeenIdx[256]; //index of the characters seen in S

}HASH;

void init_hash(HASH *hash){

    int i;
    for(i=0;i<256;i++){

        hash->H[i] = 0; // initially hash is empty
        hash->lastSeenIdx[i] = -1; // none of the chars in S are seen initially
    }
}

char* min_window_substring(char *S, char *T) {

    HASH hash;
    int i, len_T;
    int minIndex = INT_MAX, maxIndex = INT_MIN; // get the min and max index of the char in S
    int count = 0;
    init_hash(&hash);
    len_T = strlen(T);

    /*fill the hash for T*/
    for (i=0; i<len_T; i++){
        if(!hash.H[(int)T[i]])  //(int) is added to convert char into ascii
            hash.H[(int)T[i]] = 1 ;
    }

    /*for(i=0;i<256;i++){*/
        /*printf("%d %d,", hash.H[i], hash.lastSeenIdx[i]);*/
    /*}*/

    /*loop through S, char by char*/
    i=0;
    while (S[i]) {

        /*we need to update the last seen index only when char is present in hash*/
        if(hash.H[(int)S[i]]){

            hash.lastSeenIdx[i] = i;

            if (count >= len_T){

                if(hash.lastSeenIdx[i] < minIndex)
                    minIndex = hash.lastSeenIdx[i]; //store the min index
                if(hash.lastSeenIdx[i] > maxIndex)
                    maxIndex = hash.lastSeenIdx[i]; // store the max index
            }
            count++;
        }
        i++;
    }

    printf("minIndex:%d, maxIndex:%d\n", minIndex, maxIndex);
    return NULL;
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

        //printf("%d\n", (int)S[i]);

        if(hash[(int)S[i]] == '\0' && hash[(int)T[i]] == '\0') {
            hash[(int)S[i]] = T[i]; //map S char with T
            hash[(int)T[i]] = S[i]; // map T char with S

        } else {

            if(hash[(int)T[i]] != S[i])
                return 0;
        }

        i++;
    } //while ends

    for (i=0;i<256;i++)
        if(hash[i])
        printf("%c ", hash[i]);
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


/*
 * linkedin(shortest word distance)
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
        H[i].index = -1;
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
            H[S[j]-'a'].index = j;
            j++;

        }else{

            /*we have already visted the char before: check if the index lies betweeb i and j ?, if it does 
             * then update i to the next index*/
            if (H[S[j]-'a'].index >= i){
                i = H[S[j]-'a'].index + 1;
                H[S[j]-'a'].index = j;
                j++;
            }
            else{
                /*
                 *if we come here that means if are seeing a character again but it lies to the left of i and j, so we can ignore it
                 *and remove the entry from the hash table(ie mark the char as unset and set index to -1
                 */
                H[S[j]-'a'].visited = 0;
                H[S[j]-'a'].index = -1;
                /*
                 *we intentionally do not increment the j here, because we have already marked j as unvisted so next time in the top level
                 *    while loop, we want j to be counted as part on the longest string ( since the char lies outside of i and j)
                 */
            }
        }

        /*j++;*/
    }

    return max;
}

/*
 *Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length. Do not allocate extra space for another array, you must do this in place with constant memory. For example, Given input array A = [1,1,2], Your function should return length = 2, and A is now [1,2].
 */

char* remove_duplicate_in_place(char *S) {

    int len, j, i;
    if(!S)
        return NULL;

    len = strlen(S);
    if (len == 1)
        return S;
    /*
     *we take two pointer approach where 
     *    i = pointer before which all chars are non repetitive
     *    j = pointer which moves ahead as we parse the chars of string one by one
     */

    j = 1;
    i = 1;

    while (j < len) {
        //if the current char matches the prev char , just increment j
        if(S[j] == S[j-1]){
            j++;
        } else {

            S[i] = S[j];
            i++; j++;
        }

    }//while ends

    /*after the while loop i points to index next to the non-duplicate char string*/
    S[i] = '\0';

    return S;
}


/*
 *How do you find an element in an sorted array of infinite size
 *logic: 
 *
 *we start scanning the array in multuiples of 2 ( starting from 2) and run a binary search
 *
 * int find_element_infinite_array(int *A, int key){
 *
 *      len = 1;
 *      low = 0;
 *
 *      while(1) { // keep continuing the search till we find an array
 *
 *          len = len*2; //double the size of array to scanned in each iteration
 *          high = low + len - 1; //scan array from index low to high
 *
 *          if ( binsearch(A, low, high, key))
 *              return 1; // found the key 
 *
 *          else {
 *             
 *              //keep searching from the next index after high from the previous iteration
 *              low = hig+1;
 *          }
 *
 *      }//while ends
 *
 * }
 *
 *
 */


/* print all subsequence of a given string */
void print_subsequence(char *S, int len) {

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
    printf("20 -- remove duplicates from a sorted array in place\n");
    printf("21 -- print all subsequence of a string\n");



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
            reverseWordsMultipleSpaces(S);
            /*reverseWordsSingleSpace(S);*/
            //print_string(S, strlen(S));
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
            reverseWordsPreservingOrder(S);
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
            printf("Longest substring: %d",longest_substring_without_repeat_char(S));
            break;
        case 20:
            printf("Enter the string\n");
            scanf(" %s", S);
            printf("String after removing duplicates: %s",remove_duplicate_in_place(S));
            break;
        case 21:
            printf("Enter the string\n");
            scanf(" %s", S);
            print_subsequence(S, 2);
            break;

        default:
            printf("Invalid option\n");
            break;
    }
    printf("\n\n");
    /*}while((c=getchar())!='q'); */
    return 0;
}

