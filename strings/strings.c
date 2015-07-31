
#include <stdio.h>
#include <stdlib.h>

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



int main() {
    /*char c;*/
    int choice;
    char str[] = "gee  ks f  or g  ee ks ";
    char path[128];
    /*do {*/

	printf("MENU OPTIONS\n");
	printf("1 -- remove spaces from string\n");
	printf("2-- Check if a given sequence of moves for a robot is circular or not\n");
	

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

	    default:
		printf("Invalid option\n");
		break;
	}
	printf("\n\n");
    /*}while((c=getchar())!='q'); */
    return 0;
}

