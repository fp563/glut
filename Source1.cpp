#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "matrix.h"

/*

#define POINT 5

void init(void);

int width, height;
matrix points;
int next;

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



void display(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT);
	for (i = 0; i < POINT; i++) {
		glBegin(GL_POINTS);
		glVertex2d(mat_elem(points, i, 0), mat_elem(points, i, 1));
		glEnd();
	}

	for (double j = 0; j < width; j += 0.1) {
		glBegin(GL_LINES);
		glVertex2d(j - 0.1 / 2., lagrange(j - 0.1 / 2., points));
		glVertex2d(j + 0.1 / 2., lagrange(j + 0.1 / 2., points));
		glEnd();
	}

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	width = w;
	height = h;
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			mat_elem(points, next, 0) = x;
			mat_elem(points, next, 1) = height - y;
			next++;
			if (next > POINT) next = 0;
			glutPostRedisplay();
		}
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glPointSize(5.0);
	if (mat_alloc(&points, POINT, 2)) exit(-1);
	next = 0;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}

*/