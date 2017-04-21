/*
 *Common utility file for all data strcutures 
 */
#ifndef	_UTIL_H_
#define	_UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <string.h>



int max_node(int a, int b, int c);
int MAX(int a, int b);
int MIN(int a, int b);
int MIN_three(int a, int b, int c);
int MAX_three(int a, int b, int c);
int MOD(int x, int y);
void init_array(int *arr, int n);
void init_2Darray(int **A, int r, int c, int val);
void init_2Dchar_array(char **A, int r, int c, char val);
int* create_1Darray(int n);
int** create_1D_array_ptr(int n);
int** create_2Darray(int xlen, int ylen);
int** create_2Dmatrix(int xlen, int ylen);
char ** create_2Dchar_array(int r, int c);
char* create_1Dchar_array(int n);
void input_array(int *A, int n);
void input_2Darray(int **A, int r, int c);
void input_1Darray(int *A, int n);
void input_2Dchar_array(char**A, int r, int c);
void print_2Dchar_array(char **T, int xlen, int ylen);
void print_2Dmatrix(int **T, int xlen, int ylen);
void print_2Darray(int **t, int xlen, int ylen);
void print_1Darray(int *A, int n);
void swap(int *A, int idx1, int idx2);
void swap_str(char *A, int idx1, int idx2);

#endif /*   _UTIL_H_ */ 
