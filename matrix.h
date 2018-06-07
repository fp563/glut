#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//repetition
//------------------------------------------
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)


#define FROM0
#define MAT_EPS 1.0e-8
#define mat_elem(mat,i,j)  ((mat).element[(i)*((mat).col)+(j)])


typedef struct {
	int row;
	int col;
	double *element;
} matrix;

int mat_alloc(matrix *mat1, int row, int col);
void mat_free(matrix *mat1);
void mat_print(matrix mat1);
int mat_copy(matrix *mat1, matrix mat2);
int mat_add(matrix *mat1, matrix mat2, matrix mat3);
int mat_sub(matrix *mat1, matrix mat2, matrix mat3);
int mat_mul(matrix *mat1, matrix mat2, matrix mat3);
int mat_muls(matrix *mat1, matrix mat2, double c);
int mat_trans(matrix *mat1, matrix mat2);
int mat_unit(matrix *mat1);
int mat_compare(matrix mat1, matrix mat2);
int mat_solve(matrix *x, matrix a, matrix b);
int mat_solve2(matrix *x, matrix a, matrix b);
int mat_solve_pivot(matrix *x, matrix a, matrix b);
int mat_inverse(matrix *s, matrix a);
int mat_row_swap(matrix *x, int r1, int r2);
int mat_least_square(matrix *a, matrix points, int order);
double lagrange(double x, matrix points);

#endif