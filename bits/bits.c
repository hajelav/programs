/*##################################################################################
 *ASSUMPTION : All integers are assumed to be 32-bit for this file  
 *#################################################################################*/

/*
 * Important things to remember for bitwise operators

 * 1. Subtraction of 1 from a number toggles all the bits (from right to left) till the rightmost set bit(including the righmost set bit). So if we subtract a number by 1 and do bitwise & with itself (n & (n-1)), we unset the righmost set bit. 
   2. (n & -n ) gives the position of first set bit(from right) in number n 
   3. to flip a bit, XOR that bit with 1.
   4. if the bit is XORed with 0, it remains same
 *
 */

#include "../utils.h"

void printBinary(uint32_t n){

    uint32_t i, j=31;
    uint32_t A[32];
    int count = 0;

    for(i=0;i<32;i++){
        A[j] = n%2;
        j--;
        n = n/2;
    }

    for(i=0;i<32;i++){
        count++;
        printf("%u", A[i]);
        if(count == 4){
            printf(" ");
            count = 0;
        }

    }
}

int get2compliment(int n){
    return(~n + 1);
}

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


/* leetcode problem 190
 * Reverse Bits of a Number (Method 2)
 */

uint32_t reverse_bits(uint32_t n){

    int i;
    uint32_t res = 0;
    uint32_t rightmostBit;

    for(i=31;i>=0;i--){
	/*
	 *logic : extract the leftmost bit of n (n&1) , and then shift that bit to j places(<<j)
	 *        where j start from 31 to 0. keep on ORing the result from the previous value
	 */
	rightmostBit = n&1;// get the rightmost bit

	res = res | ( rightmostBit << i);
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

    int moveLeft, moveRight;
    /*move the 'by' number of bits to the left end*/
    moveLeft = n<<(32-by);
    
    /*move the 'by' number of bits to the right end*/
    moveRight = n>>by;

    return (moveLeft|moveRight);
}


/*
 *leetcode problem 260
 *https://leetcode.com/problems/single-number-iii/
 *Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.
 *
logic : let x and y be the two elements that appear only once. the set bits(1) in xor will give all the bits that set(1) in x and unset(0) in y
or unset(0) and set(1) in y. Now we need to divide the array(A) elements into two groups - one set of elements with same bit set and other set with same bit not set. By doing so, we will get x in one set and y in another set. Now if we do XOR of all the elements in first set, we will get first non-repeating element, and by doing same in other set we will get the second non-repeating element.

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
    set_bit_no = xor & ~(xor-1); // xor & -xor

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

int swapEvenOddBits(unsigned int n) {
{
    unsigned int even_bits, odd_bits;

    /*get all even bits*/
    even_bits  = n & 0x55555555; //(OEOE OEOE)

    /*Get all odd bits*/
    odd_bits = x & 0xAAAAAAAA; //(1010101010101010)


    odd_bits >>= 1;  // Right shift even bits
    even_bits <<= 1;   // Left shift odd bits

    return (even_bits | odd_bits); // Combine even and odd bits
}

void print_subsets(int *A, int num, int n) {


    /*printf("number : %d\n", num);*/
    int pos; 
    while(num>0){

	//get the position of the first set bit of num
	pos = log2(num & (-num));
	/*printf("pos : %d\n", pos);*/

	printf("%d ", A[pos]);

	//set the position of the first set bit to 0
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
 *leetcode problem 89
 *The gray code is a binary numeral system where two successive values differ in only one bit.
 *
 *Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.
 *
 *For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
 *
 *00 - 0
 *01 - 1
 *11 - 3
 *10 - 2
 *Note:
 *For a given n, a gray code sequence is not uniquely defined.
 *
 *For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.
 */

void gray_code(int n) {


    int nbits, count = 1, k = 1, i = 1;
    int prev, num;
    int *A;
    if(n==0)
	return;

    nbits = 1<<n;

    A = (int*)calloc(nbits, sizeof(int)); //array to store the sequence of gray code
    memset(A, -1, sizeof(int)*nbits);
    A[0] = 0;
    prev = A[0];

    /*run the while loop till array of size nbits is not filled completely*/
    while(count <= nbits){

	num = prev ^ (i%nbits);
	if((A[i%nbits]== -1) && ((num & (num-1)) == 0)){
	    count++;
	    A[k] = i%nbits;
	    printf("%d ", i%nbits);
	    prev = A[k];
	    k++;

	}
	i++;
    }

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
	printf("15 -- gray code\t");

	

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

	case 15:		
		printf("enter no of elements in the array\n");
		scanf("%d", &n);
		gray_code(n);
		break;

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}

