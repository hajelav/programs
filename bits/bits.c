/*
 * Important things to remember for bitwise operators

 * 1. Subtraction of 1 from a number toggles all the bits (from right to left) till the rightmost set bit(including the righmost set bit). So if we subtract a number by 1 and do bitwise & with itself (n & (n-1)), we unset the righmost set bit. 
   2. (n & -n ) gives the position of first set bit(from right) in number n 
   3. to flip a bit, XOR that bit with 1.
 *
 */

#include "../utils.h"
/*
 * leetcode problem 191
 * Write a C program to find the parity of an unsigned integer
 * http://www.geeksforgeeks.org/category/bit-magic/page/4/
 */

int findParityUnsignedInt(unsigned int n){

    int count = 0;
    while(n>0){
	if(n&1)
	    count++;
	n = n>>1;
    }
    return count;
}

/*
 * Write an Efficient Method to Check if a Number is Multiple of 3
 * http://www.geeksforgeeks.org/write-an-efficient-method-to-check-if-a-number-is-multiple-of-3/
 */

/*
 * logic : calculate the differene between count of odd and even count set bits
 * if it is multiple of 3 , then the number is a multiple of 3. function return 1 or 0
 */
int checkMultipleOf3(int n){

    int even_c = 0, odd_c = 0;

    if(n<0)
	n = -n;
    if (n == 0)
	return 1;
    if(n == 1)
	return 0;

    while(n > 0){

	if(n&1)
	    odd_c++;
	n = n>>1;
	if(n&1)
	    even_c++;

	n = n>>1;
    }
    return(abs(odd_c - even_c));
}

int rightMostSetBit( int n) {

    int cnt = 0;
    while(n>0){
	if(n&1)
	    return ++cnt;
	cnt++;
	n = n>>1;
    }
    return cnt;
}

/*
 *another method to calculate the rightmost set bit
 */

/*
 *int rightMostSetBit( int n) {
 *    return ((log(n&(-n)) / (log 2)) + 1); 
 *    log 2;
 *}
 */

/*
 *Write an Efficient C Program to Reverse Bits of a Number (Method 1)
 */

/*
 *int reverseBits(int n){
 *
 *    int temp, sum = 0;
 *    temp = n;
 *    int cnt=-1;
 *    //get the number of bits in the number
 *    while(n>0){
 *        cnt++;
 *        n = n>>1;
 *    }
 *
 *    while(temp > 0){
 *        sum += (temp&1)<<cnt;
 *        cnt--;
 *        temp = temp>>1;
 *    }
 *
 *    return sum;
 *}
 */

void printBinary(uint32_t n){

    uint32_t i, j=31;
    uint32_t A[32];

    for(i=0;i<32;i++){
	A[j] = n%2;
	j--;
	n = n/2;
    }

    for(i=0;i<32;i++){
	printf("%u", A[i]);
    }
}

/* leetcode problem 190
 * Reverse Bits of a Number (Method 2)
 */
uint32_t reverse_bits(uint32_t n){

    uint32_t i, j = 31;
    uint32_t res = 0;

    for(i=0;i<32;i++){
	/*
	 *logic : extract the leftmost bit of n (n&1) , and then shift that bit to j places(<<j)
	 *        where j start from 31 to 0. keep on ORing the result from the previous value
	 */

	res = res | ((n&1) << j);
	j--;
	n = n>>1;
    }

    printBinary(res);
    return res;
}

/*
 * Count set bits in an integer
 * http://www.geeksforgeeks.org/count-set-bits-in-an-integer/
 */
int countSetBits(int n){
    int cnt =0;
    while(n>0){
	n &=n-1;
	cnt++;
    }
    return cnt;
}

int getBits(int n){

    int cnt = 0;
    while(n>0){
	cnt++;
	n = n>>1;
    }
    return cnt;
}

int rotateBitsRight(unsigned int n, int by) {

    int nbits, temp;
    nbits = getBits(n);
    printf("nbits:%d\n", nbits);
    temp = n;

    n = n>>by;
    temp = temp & ((1<<by)-1);
    temp = temp<<(nbits-by); 
    return n|temp;
}



/*
 *Find the two non-repeating elements in an array of repeating elements
http://www.geeksforgeeks.org/find-two-non-repeating-elements-in-an-array-of-repeating-elements/
 */


/*  This finction sets the values of *x and *y to nonr-epeating
 *   elements in an array arr[] of size n*/
void get2NonRepeatingNos(int arr[], int n, int *x, int *y)
{
    int xor = arr[0]; /*  Will hold xor of all elements */
    int set_bit_no;  /*  Will have only single set bit of xor */
    int i;
    *x = 0;
    *y = 0;

    /*  Get the xor of all elements */
    for(i = 1; i < n; i++)
	xor ^= arr[i];

    /*  Get the rightmost set bit in set_bit_no */
    set_bit_no = xor & ~(xor-1);

    /*  Now divide elements in two sets by comparing rightmost set
     *     bit of xor with bit at same position in each element. */
    for(i = 0; i < n; i++)
    {
	if(arr[i] & set_bit_no)
	    *x = *x ^ arr[i]; /* XOR of first set */
	else
	    *y = *y ^ arr[i]; /* XOR of second set*/
    }
} 


int powerOf4(int n){

    if(n==0)
	return 1;
    int nbits;
    
    nbits = getBits(n);
    return (n ^ (1<<(nbits-1)));

}
 
/*
 *Write a program to add one to a given number. You are not allowed to use operators like ‘+’, ‘-‘, ‘*’, ‘/’, ‘++’, ‘–‘ …etc.
 */

/*
 *logic : we have to make all 1's as 0 untill we encounter a 0 in n + flip the first 0 found.
*/
int add1(unsigned int n) {

    int temp, cnt = 0;
    temp = n;

    int BIT_MAX = 32;
    
    while(BIT_MAX){
	//check if 0 is found
	if(!(n&1)){
	    //make  found before 0 , as 1
	    temp = temp | (1<<(cnt));
	    //make all 1s after this found 0 as 0s
	    temp = temp & (-1<<(cnt));
	    return temp;
	}	
	cnt++;
	n = n>>1;
	BIT_MAX--;
    }

    return 1;
}

/*
 *Count total set bits in all numbers from 1 to n
 */




/*
 *Swap bits in a given number
 */
 /*
  *logic : we get the position of x and y, if both are 0s or 1s we dont have to swap.
  *if different , then we just need to flip the bit at the corresponding positions X and Y
  flipping of bits can be done by XORing the bit with 1
  */

int swapBits(int n, int x, int y) {

    int pos_x, pos_y;

    pos_x = (n>>x)&1;
    pos_y = (n>>y)&1;

    //if bits are diff (ie XOR of bits is 1) then swap
    if(pos_x ^ pos_y) {
	//xor the oringinal number with 1s at x and y position;
	//if u XOR a bit with 1 , it gets flipped, if you XOR with 0 , it remains same
	return(n ^ ((1<<x)|(1<<y)));
    }

    //return the same no as we dont need to swap 
    return n;
}


/*
 *Add two numbers without using arithmetic operators
 *http://www.geeksforgeeks.org/category/bit-magic/page/2/
 */


/*
 *Swap all odd and even bits (method 1)
 *http://www.geeksforgeeks.org/swap-all-odd-and-even-bits/
 */

/*
 *int swapEvenOddBits(int n) {
 *    int x =3;
 *    int temp = n;
 *
 *    while(n){
 *
 *        //bits at evn-odd postions are different(01 or 10), so we need to swap
 *        if(((n & 3) == 1) || ((n & 3) ==2)){
 *            //xor the bits(01 or 10) with 11 to get the bits swapped
 *            temp = temp^x;
 *        }
 *        //move 000011 pattern from right to left
 *        x = x<<2;
 *        n = n>>2;
 *    }
 *    return temp;
 *}
 */


 /*
  *Swap all odd and even bits (method 2)
  */

int swapEvenOddBits(int n) {

    int x,y;
     x = (n & 0x55555555) << 1;
     y = (n >> 1) & 0x55555555;

     return x|y;
}

/*
 *swap two numbers using XOR
 */

void swapNum(int x , int y){

    x = x ^ y;
    y = x ^ y;
    x = x ^ y;

    printf("%d %d", x, y);
}

/*
 *swap even and odd nibbles 
 */

int swapNibbles(int n) {
    
    int x, y;
     x = (n & 0x0F0F0F0F) << 4;
     y = (n >> 4) & 0x0F0F0F0F;
     
     return x|y;
}

void print_subsets(int *A, int num, int n) {


    /*printf("number : %d\n", num);*/
    int pos; 
    while(num>0){

	//get the position of the first set bit of num
	pos = log2(num & (-num));
	/*printf("pos : %d\n", pos);*/

	printf("%d ", A[pos]);

	//set the position of the bit to 0
	num = num & (num-1);
    }
}

/*
 *leetcode problem 78
 *https://leetcode.com/problems/subsets/
 */


void subsets(int *A, int n) {

    int i, tot_subsets;
    tot_subsets = pow(2, n);

    printf("Subsets\n");
    for(i=1;i<tot_subsets;i++){
	print_subsets(A, i, n);
	printf("\n");
    }
}

/*
 *leetcode problem 260
 *https://leetcode.com/problems/single-number-iii/
 *Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.
 *
logic : let x and y be the two elements that appear only once. the set bits(1) in xor will give all the bits that set(1) in x and unset(0) in y
or unset(0) and set(1) in y. Now we need to divide the array(A) elements into two groups - one set of elements with same bit set and other set with same bit not set. By doing so, we will get x in one set and y in another set. Now if we do XOR of all the elements in first set, we will get first non-repeating element, and by doing same in other set we will get the second non-repeating element.
*/

void two_numbers( int *A, int len) {

    int i, rightmost_set_bit;
    int x=0, y=0;
    int xor = A[0]; 


    /*get the xor of all the elements*/
    for(i=1;i<len;i++){
	xor = xor^A[i];
    }

    /*
     *Now in xor(variable), we need to  get only one set bit(making rest other set bits to 0). This can be done by easily by considering only
     *the first set(1) bit from the right. [ Remember point 2 at the start of the file]
     */

    rightmost_set_bit = xor & (-xor);


    /*Now divide elements in two sets by comparing rightmost set bit of xor with bit at same position in each element*/
    for(i=0;i<len;i++){

	if(A[i] & rightmost_set_bit)
	    x = x ^ A[i]; /* XOR of first set */
	else
	    y = y ^ A[i]; /* XOR of second set*/
    }

    printf("two numbers : %d %d\n", x, y);

}



int main() {
    char c;
    int choice, n, shift, posx, posy;
    int *x, *y, *A;
    uint32_t N;
    int arr[] = {2, 3, 7, 9, 11, 2, 3, 11};
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Find parity of unsigned int\t");
	printf("2 -- Check multiple of 3\t");
	printf("3 -- Position of rightmost set bit\t");
	printf("4 -- Reverse the bits\t");
	printf("5 -- Count set bits in an integer\t");
	printf("6 -- Rotate bits(left|right)\t");
	printf("7 -- two non-repeating elements in an array of repeating elementst\t");
	printf("8 -- Check if a number is power of 4\t");
	printf("9 -- Add 1 to a number\t");
	printf("10 -- Swap position x and y\t");
	printf("11 -- Swap all odd and even bits\t");
	printf("12 -- Swap even and odd nibbles\t");
	printf("13 -- Given a set of distinct integers, nums, return all possible subsets\t");
	printf("14 -- Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once\t");

	

	printf("\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){
	    case 1:
		printf("enter no\n");
		scanf("%d", &n);
		printf("Parity : %d\n", findParityUnsignedInt(n));
		break;
	    case 2:
		printf("enter no\n");
		scanf("%d", &n);
		printf("Multiple of 3 : %s\n", checkMultipleOf3(n)?"no":"yes");
		break;
	    case 3:
		printf("enter no\n");
		scanf("%d", &n);
		printf("Pos of rightmost set bit : %d\n", rightMostSetBit(n));
		break;
	    case 4:
		printf("enter no\n");
		scanf("%d", &N);
		printBinary(N);
		printf("\n");
		printf("\nreversed number : %u\n", reverse_bits(N));
		break;
	    case 5:
		printf("enter no\n");
		scanf("%d", &n);
		printf("No of set bits: %d", countSetBits(n));
		break;
	    case 6:
		printf("enter no and shift\n");
		scanf("%d\n%d", &n, &shift);
		printBinary(n);
		printf("\n");
		/*rotateBitsRight(n, shift);*/
		printBinary(rotateBitsRight(n, shift));
		/*printf("%d", rotateBitsRight(n, shift));*/
		break;

	    case 7:
		 x = (int *)malloc(sizeof(int));
		y = (int *)malloc(sizeof(int));
		get2NonRepeatingNos(arr, 8, x, y);
		printf("The non-repeating elements are %d and %d", *x, *y);
		break;

	    case 8:
		printf("enter no\n");
		scanf("%d", &n);
		printf("Power of 4 : %s", powerOf4(n)?"no":"yes");
		break;

	    case 9:
		printf("enter no\n");
		scanf("%d", &n);
		printf("Add 1 to %d : %d", n, add1(n));
		break;

	    case 10: 
		printf("enter no\n");
		scanf("%d", &n);
		printf("enter position x and y\n");
		scanf("%d\n%d", &posx, &posy);
		printBinary(n);
		printf("\n");
		printBinary(swapBits(n, posx-1, posy-1));
		break;

	    case 11:
		printf("enter no\n");
		scanf("%d", &n);
		printBinary(n);
		printf("\n");
		printf("%d\n",swapEvenOddBits(n));
		printBinary(swapEvenOddBits(n));
		break;

	    case 12:
		printf("enter no\n");
		scanf("%d", &n);
		printBinary(n);
		printf("\n");
		printf("%d\n",swapNibbles(n));
		printBinary(swapNibbles(n));
		break;

	    case 13:
		printf("enter no of elements in the array\n");
		scanf("%d", &n);

		printf("Enter numbers\n");

		A = create_1Darray(n);
		input_array(A, n);
		subsets(A, n);
		free(A);

	    case 14:
		printf("enter no of elements in the array\n");
		scanf("%d", &n);
		printf("Enter numbers\n");

		A = create_1Darray(n);
		input_array(A, n);
		two_numbers(A, n);
		free(A);
		break;

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}

