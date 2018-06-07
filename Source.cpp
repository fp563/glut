/*

#include <windows.h>
#include <GL/gl.h> //MAC の人はこの行を消す
#include <GL/glut.h> //MAC の人は GL を glut に変更

void init(void);
int width, height;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex2d(100, 200);
	glVertex2d(300, 200);
	glVertex2d(200, 100);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(100, 140);
	glVertex2d(100, 0);
	glVertex2d(180, 0);
	glVertex2d(180, 60);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(220, 60);
	glVertex2d(220, 0);
	glVertex2d(300, 0);
	glVertex2d(300, 140);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(101, 200);
	glVertex2d(101, 130);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(300, 200);
	glVertex2d(300, 130);
	glEnd();


	glColor3d(1.0, 0.0, 0.0);
	glPointSize(20.0);
	glBegin(GL_POINTS);
	glVertex2d(280, 20);
	glEnd();

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


void init(void)
{
	glClearColor(0.0, 0.0, 1.0, 0.0);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	init();

	glutMainLoop();
	return 0;
}


*/