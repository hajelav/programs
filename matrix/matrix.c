#include "../utils.h"

/*http://stackoverflow.com/questions/20577117/algorithm-to-modify-a-matrix-and-set-columns-and-rows-to-zero*/
/*
 *Time : O(n2)
 *space : O(1)
 */
void row_col_zero(int **A, int row, int col) {

    int r, c;
    int setFirstRow = 0;//to check if we find 0 in first row
    int setFirstCol = 0;//to check if we find 0 in first col

    if(!(*A)|| row<=0 || col<=0)
	return;

    printf("Input array\n");
    print_2Darray(A, row, col);

    /*first pass: traverse through first row and column and check if we find a 0*/

    for(c=0;c<col;c++){
	if(A[0][c] == 0)
	    setFirstRow = 1;
    }

    for(r=0;r<row;r++){
	if(A[r][0] == 0)
	    setFirstCol = 1;
    }

/*
 *second pass: go through the matrix row-1 and col-1 and look for any 0, if found update the first row and colum
 *here the first row and column serve as auxillary array
 */
    for(r=1;r<row;r++){
	for(c=1;c<col;c++){
	    if(A[r][c] == 0){
		//make first element of that row and column as 0
		A[r][0] = 0;
		A[0][c] = 0;
	    }
	}
    }

    /*third pass: go through the row-1 , col-1 array, and whenever u find corresponding 0 in first row or first column , mark that element is zero*/

    for(r=1;r<row;r++){
	for(c=1;c<col;c++){
	    if(A[r][0] == 0 ||  A[0][c] == 0){
		A[r][c] = 0;
	    }
	}
    }

    /*fourth pass: go through the first row and colum and set all elements as 0 if you find varibles set in first pass*/
    if(setFirstRow) {
	for(c=0;c<col;c++){
	    A[0][c] = 0;
	}
    }

    if(setFirstCol) {
	for(r=0;r<row;r++){
	    A[r][0] = 0;
	}
    }

    printf("Output array\n");
    print_2Darray(A, row, col);
}

int** rotate_matrix(int r, int c) {

    return NULL;
}

void search_matrix(int **A, int row, int col) {

}


/**
 * linkedin
 * http://www.careercup.com/question?id=6482755168763904
 *
 ** Given a matrix of following between N LinkedIn users (with ids from 0 to N-1): 
 ** followingMatrix[i][j] == true if user i is following user j 
 ** thus followingMatrix[i][j] doesn't imply followingMatrix[j][i]. 
 ** Let's also agree that followingMatrix[i][i] == false 
 ** 
 ** Influencer is a user who is: 
 ** - followed by everyone else and 
 ** - not following anyone himself 
 ** 
 ** This method should find an Influencer by a given matrix of following, 
 ** or return -1 if there is no Influencer in this group. 

# Example of m users(0, 1, 2,3)
m = [[0, 1, 1, 0],
     [1, 0, 1, 1],
     [0, 0, 0, 0],
     [1, 1, 1, 0]]

  influencer : 2 since he is not following anyone and is being followed by 0, 1, 3
 **/ 

int get_influencer() {

    int **follow;
    int i, j, users;
    int count=0;

    printf("enter number of users\n");
    scanf("%d", &users);

    /*create follow array*/
    follow = create_2Darray(users, users);
    input_2Darray(follow, users, users);

    /*
     *to find out influencer
     *    1. first we find out the user who is not following anyone, ie we should find row with all zeros(say ith row)
     *    2. next if we find a user in step 1, now we find if all other users are following him, ie: ith colum should have all 1(except ith row)
     */


    /*step :1*/
    for(i=0;i<users;i++){
	for(j=0;j<users;j++){

	    if(i!=j && follow[i][j] == 0 && follow[j][i] == 1)
		count++;
	}
	if(count==users-1)
	    return i;
	count = 0;
    }
    return -1;
}

int main(){
    char c;
    int choice;
    int row, col;
    int **A;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Rotate matrix by 90 degree\n");
	printf("2 -- Make entire row and column zero , if you find an element as zero\n");
	printf("3 -- search in a 2D matrix whose rows and columns are sorted\n");
	printf("4 -- get influencer\n");
	printf("\n");
	printf("Enter your choice\n");
	scanf("%d",&choice);
	switch(choice){
	    case 1:
		printf("Enter no of rows\n");
		scanf("%d", &row);
		printf("Enter no of cols\n");
		scanf("%d", &col);

		A = rotate_matrix(row, col);
		print_2Dmatrix(A, col, row);
		break;

	    case 2:
		printf("Enter no of rows\n");
		scanf("%d", &row);
		printf("Enter no of cols\n");
		scanf("%d", &col);
		A = create_2Darray(row, col);
		input_2Darray(A, row, col);
		row_col_zero(A, row, col);
		break;

	    case 3: 
		printf("Enter no of rows\n");
		scanf("%d", &row);
		printf("Enter no of cols\n");
		scanf("%d", &col);
		A = create_2Darray(row, col);
		input_2Darray(A, row, col);
		search_matrix(A, row, col);
		break;

	    case 4:
		printf("influencer : %d\n", get_influencer());
		break;

	    default:
		printf("invalid option\n");

	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
