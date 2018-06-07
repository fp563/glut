#include "matrix.h"

int mat_alloc(matrix *mat1, int row, int col) {

	mat1->element = (double*)calloc(row*col, sizeof(double));
	if (mat1->element == NULL) {
		printf("error\n");
		exit(-1);
	}
	mat1->row = row;
	mat1->col = col;
	return 0;
}

void mat_free(matrix *mat1) {
	free(mat1->element);
}

void mat_print(matrix mat1) {
	REP(i, mat1.row) {
		REP(j, mat1.col) {
			printf("%4.2f  ", mat_elem(mat1, i, j));
		}
		printf("\n");
	}
}

int mat_copy(matrix *mat1, matrix mat2) {
	if ((mat1->row != mat2.row) || (mat1->col != mat2.col)) {
		return (-1);
	}
	REP(i, mat1->row) {
		REP(j, mat1->col) {
			mat_elem(*mat1, i, j) = mat_elem(mat2, i, j);
		}
	}
	return 0;
}

int mat_add(matrix *mat1, matrix mat2, matrix mat3)
{
	if ((mat1->row != mat2.row) || (mat1->col != mat2.col)) {
		return (-1);
	}
	if ((mat1->row != mat3.row) || (mat1->col != mat3.col)) {
		return (-1);
	}
	REP(i, mat2.row) {
		REP(j, mat2.col) {
			mat_elem(*mat1, i, j) = mat_elem(mat2, i, j) + mat_elem(mat3, i, j);
		}
	}
	return 0;
}

int mat_sub(matrix *mat1, matrix mat2, matrix mat3)
{
	if ((mat1->row != mat2.row) || (mat1->col != mat2.col)) {
		return (-1);
	}
	if ((mat1->row != mat3.row) || (mat1->col != mat3.col)) {
		return (-1);
	}
	REP(i, mat2.row) {
		REP(j, mat2.col) {
			mat_elem(*mat1, i, j) = mat_elem(mat2, i, j) - mat_elem(mat3, i, j);
		}
	}
	return 0;
}

int mat_mul(matrix *mat1, matrix mat2, matrix mat3)
{
	if ((mat1->row != mat2.row) || (mat1->col != mat2.col)) {
		return (-1);
	}
	if ((mat1->row != mat3.row) || (mat1->col != mat3.col)) {
		return (-1);
	}
	if (mat2.col != mat3.row) {
		return (-1);
	}

	matrix matt;
	mat_alloc(&matt, mat1->row, mat1->col);
	REP(i, mat2.row) {
		REP(j, mat3.col) {

			double temp = 0;
			REP(k, mat3.row) {
				temp += mat_elem(mat2, i, k) * mat_elem(mat3, k, j);
			}
			mat_elem(matt, i, j) = temp;
		}
	}
	mat_copy(mat1, matt);
	mat_free(&matt);

	return 0;
}

int mat_muls(matrix *mat1, matrix mat2, double c) {
	if ((mat1->row != mat2.row) || (mat1->col != mat2.col)) {
		return (-1);
	}
	REP(i, mat2.row) {
		REP(j, mat2.col) {
			mat_elem(*mat1, i, j) = mat_elem(mat2, i, j) * c;
		}
	}
	return 0;
}

int mat_trans(matrix *mat1, matrix mat2) {
	if ((mat1->row != mat2.col) || (mat1->col != mat2.row)) {
		return (-1);
	}
	matrix matt;
	mat_alloc(&matt, mat1->row, mat1->col);
	REP(i, mat2.row) {
		REP(j, mat2.col) {
			mat_elem(matt, i, j) = mat_elem(mat2, j, i);
		}
	}
	mat_copy(mat1, matt);
	mat_free(&matt);
	return 0;
}

int mat_unit(matrix *mat1) {
	if ((mat1->row != mat1->col)) {
		return (-1);
	}
	REP(i, mat1->row) {
		REP(j, mat1->col) {
			if (i == j) {
				mat_elem(*mat1, i, j) = 1;
			}
			else {
				mat_elem(*mat1, i, j) = 0;
			}
		}
	}
	return 0;
}

int mat_compare(matrix mat1, matrix mat2) {
	if ((mat1.row != mat2.row) || (mat1.col != mat2.col)) {
		return (-1);
	}
	int flag = 1;
	REP(i, mat1.row) {
		REP(j, mat1.col) {
			if (mat_elem(mat1, i, j) != mat_elem(mat2, i, j)) {
				return 0;
			}
		}
	}
	return 1;
}

int mat_solve(matrix *x, matrix a, matrix b) {

	matrix a2, b2;

	if (a.row != a.col) return (-1);
	if ((b.col != 1) || (a.col != b.row)) return (-1);
	if ((x->row != b.row) || (x->col != 1)) return (-1);

	if (mat_alloc(&a2, a.row, a.col)) return (-1);
	if (mat_alloc(&b2, b.row, b.col)) return (-1);

	mat_copy(&a2, a);
	mat_copy(&b2, b);

	int n = a2.col;

	FOR(k, 0, n - 1) {
		FOR(i, k + 1, n - 1) {
			double w = mat_elem(a2, i, k) / mat_elem(a2, k, k);

			FOR(j, k, n - 1) {
				mat_elem(a2, i, j) = mat_elem(a2, i, j) - mat_elem(a2, k, j) * w;
			}

			mat_elem(b2, i, 0) = mat_elem(b2, i, 0) - mat_elem(b2, k, 0) * w;

		}
	}

	for (int i = n - 1; i >= 0; --i) {
		double sum = mat_elem(b2, i, 0);

		FOR(j, i + 1, n) {
			sum = sum - mat_elem(a2, i, j)*mat_elem(b2, j, 0);
		}
		mat_elem(b2, i, 0) = sum / mat_elem(a2, i, i);
	}

	mat_copy(x, b2);

	mat_free(&a2);
	mat_free(&b2);
	return 0;
}

int mat_solve2(matrix *x, matrix a, matrix b) {



	if (a.row != a.col) return (-1);
	if (a.col != b.row) return (-1);
	if ((x->row != b.row) || (x->col != b.col)) return (-1);


	int n = a.col;

	FOR(c, 0, b.col - 1) {
		matrix a2, b2;
		if (mat_alloc(&a2, a.row, a.col)) return (-1);
		if (mat_alloc(&b2, b.row, b.col)) return (-1);
		mat_copy(&a2, a);
		mat_copy(&b2, b);

		FOR(k, 0, n - 1) {
			FOR(i, k + 1, n - 1) {
				double w = mat_elem(a2, i, k) / mat_elem(a2, k, k);

				FOR(j, k, n - 1) {
					mat_elem(a2, i, j) = mat_elem(a2, i, j) - mat_elem(a2, k, j) * w;
				}

				mat_elem(b2, i, c) = mat_elem(b2, i, c) - mat_elem(b2, k, c) * w;

			}
		}

		for (int i = n - 1; i >= 0; --i) {
			double sum = mat_elem(b2, i, c);

			FOR(j, i + 1, n) {
				sum = sum - mat_elem(a2, i, j)*mat_elem(b2, j, c);
			}
			mat_elem(b2, i, c) = sum / mat_elem(a2, i, i);
		}

		REP(i, n) {
			mat_elem(*x, i, c) = mat_elem(b2, i, c);
		}
		mat_free(&a2);
		mat_free(&b2);
	}


	return 0;
}


int mat_row_swap(matrix *x, int r1, int r2) {

	matrix a;
	if (mat_alloc(&a, x->row, x->col)) return (-1);
	mat_copy(&a, *x);

	REP(i, x->col) {
		mat_elem(*x, r1, i) = mat_elem(a, r2, i);
		mat_elem(*x, r2, i) = mat_elem(a, r1, i);
	}

	mat_free(&a);

	return 0;
}

int mat_solve_pivot(matrix *x, matrix a, matrix b) {

	if (a.row != a.col) return (-1);
	if (a.col != b.row) return (-1);
	if ((x->row != b.row) || (x->col != b.col)) return (-1);


	int n = a.col;

	FOR(c, 0, b.col - 1) {
		matrix a2, b2;
		if (mat_alloc(&a2, a.row, a.col)) return (-1);
		if (mat_alloc(&b2, b.row, b.col)) return (-1);
		mat_copy(&a2, a);
		mat_copy(&b2, b);


		FOR(k, 0, n - 2) {

			double max = fabs(mat_elem(a2, k, k));
			int maxp = k;
			FOR(p, k + 1, n - 1) {
				if (fabs(mat_elem(a2, p, k)) > max) {
					max = fabs(mat_elem(a2, p, k));
					maxp = p;
				}
			}

			mat_row_swap(&a2, k, maxp);
			mat_row_swap(&b2, k, maxp);

			//mat_print(a2);

			FOR(i, k + 1, n - 1) {
				double w = mat_elem(a2, i, k) / mat_elem(a2, k, k);

				FOR(j, k, n - 1) {
					mat_elem(a2, i, j) = mat_elem(a2, i, j) - mat_elem(a2, k, j) * w;
				}

				mat_elem(b2, i, c) = mat_elem(b2, i, c) - mat_elem(b2, k, c) * w;

			}
			//mat_print(a2);
		}

		for (int i = n - 1; i >= 0; --i) {
			double sum = mat_elem(b2, i, c);

			FOR(j, i + 1, n - 1) {
				sum = sum - mat_elem(a2, i, j)*mat_elem(b2, j, c);
			}
			mat_elem(b2, i, c) = sum / mat_elem(a2, i, i);
		}
		//mat_print(b2);

		REP(i, n) {
			mat_elem(*x, i, c) = mat_elem(b2, i, c);
		}
		mat_free(&a2);
		mat_free(&b2);
	}
	return 0;
}


int mat_inverse(matrix *s, matrix a) {
	if (a.row != a.col) return (-1);
	if (s->row != s->col) return (-1);
	if (a.row != s->row) return (-1);

	matrix I;
	if (mat_alloc(&I, a.row, a.col)) return (-1);
	mat_unit(&I);

	matrix a2;
	if (mat_alloc(&a2, a.row, a.col)) return (-1);
	mat_copy(&a2, a);


	mat_solve_pivot(s, a2, I);


	mat_free(&I);
	mat_free(&a2);

	return 0;
}

int mat_least_square(matrix *a, matrix points, int order) {
	matrix G, F;
	if (mat_alloc(&G, order + 1, order + 1)) return (-1);
	if (mat_alloc(&F, order + 1, 1)) return (-1);

	REP(i, order + 1) {
		mat_elem(F, i, 0) = 0;
		REP(j, order + 1) {
			mat_elem(G, i, j) = 0;
			REP(k, points.row) {
				mat_elem(G, i, j) += pow(mat_elem(points, k, 0), i)*pow(mat_elem(points, k, 0), j);
			}
		}
	}

	REP(i, order + 1) {
		REP(j, points.row) {
			mat_elem(F, i, 0) += pow(mat_elem(points, j, 0), i)*mat_elem(points, j, 1);
		}
	}


	mat_solve_pivot(a, G, F);

	mat_free(&G);
	mat_free(&F);

	return 0;
}


double lagrange(double x, matrix points)
{
	double sum = 0;
	double y;
	REP(i, points.row) {
		y = 1;
		REP(j, points.row) {
			if (j != i) {
				y *= (x - mat_elem(points, j, 0)) / (mat_elem(points, i, 0) - mat_elem(points, j, 0));

			}
		}
		y *= mat_elem(points, i, 1);
		sum += y;
	}

	return sum;
}