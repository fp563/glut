#include "matrix.h"

double lagrange(double x, matrix points);

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