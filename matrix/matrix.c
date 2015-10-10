#include "../utils.h"

/*http://stackoverflow.com/questions/20577117/algorithm-to-modify-a-matrix-and-set-columns-and-rows-to-zero*/
void row_col_zero(int **A, int row, int col) {

    int r, c;
    printf("Input array\n");
    print_2Darray(A, row, col);

    /*first pass: traverse through the matrix , whenever you find a 0, make the first last element of  that row and colum as 0*/

    for(r=0;r<row;r++){
	for(c=0;c<col;c++){
	    if(A[r][c] == 0){
		//make first and last element of that row as 0
		A[r][0] = A[r][col-1] = 8;
		//make first and last element of that col as 0
		A[0][c] = A[row-1][c] = 8;
	    }
	}
    }

    printf("after first pass\n");
    print_2Darray(A, row, col);
    /*second pass: go through all the cols and fill all such colums with zero, where you find first and last element as zero*/
    for(c=0;c<col;c++){
	//check for first and last element of that col
	if(A[0][c] == 8 && A[row-1][c] == 8){
	    for(r=0;r<row;r++){
		A[r][c] = 0;
	    }
	}
    }
    printf("after second pass\n");
    print_2Darray(A, row, col);

    /*third pass: go through all the rows and fill all such rows with zero, where you find first and last element as zero*/
    for(r=0;r<row;r++){
	//check for first and last element of that col
	if(A[r][0] == 8 || A[r][col-1] == 8) {
	    for(c=0;c<col;c++){
		A[r][c] = 0;
	    }
    }
}

    printf("after third pass\n");
    print_2Darray(A, row, col);

}

int** rotate_matrix(int r, int c) {

    return NULL;
}

int main(){
    char c;
    int choice;
    int row, col;
    int **A;
    do {

	printf("MENU OPTIONS\n");
	printf("1 -- Rotate matrix by 90 degree\n");
	printf("2 -- Make entire row and col zero , if you find an element as zero\n");
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


	}
	printf("\n\n");
    }while((c=getchar())!='q'); 
    return 0;
}
