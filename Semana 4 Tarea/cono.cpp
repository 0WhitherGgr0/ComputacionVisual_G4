#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

float dameX(float R, int N, int n);
float dameZ(float R, int N, int n);
void anillo(float R, float y, int N);
void conoAlambre(float altura, float radioBase, int N);

float dameX(float R, int N, int n) {
	return R * cos(n * (2 * M_PI) / N);
}

float dameZ(float R, int N, int n) {
	return R * sin(n * (2 * M_PI) / N);
}

void anillo(float R, float y, int N) {
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < N; i++) {
		float x = dameX(R, N, i);
		float z = dameZ(R, N, i);
		glVertex3f(x, y, z);
	}
	glEnd();
}

void conoAlambre(float altura, float radioBase, int N) {
	float y = -altura / 2.0;
	anillo(radioBase, y, N);
	
	glBegin(GL_LINES);
	for(int i = 0; i < N; i++) {
		float x = dameX(radioBase, N, i);
		float z = dameZ(radioBase, N, i);
		glVertex3f(x, y, z);
		glVertex3f(0.0, altura / 2.0, 0.0);
	}
	glEnd();
}

void RenderShaft(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -50.0f);
	// cilindroAlambre(20);  
	conoAlambre(10.0, 5.0, 20);  
	glFlush();
}

void inicializaVista(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	inicializaVista();
}

void inicializaVentana(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(200, 30);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(RenderShaft);  
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);  
}

void iniciaOpenGL(int argc, char **argv) {
	inicializaVentana(argc, argv);
	inicializaVista();
	glutMainLoop();
}

int main(int argc, char** argv) {
	iniciaOpenGL(argc, argv);
	return 1;
}

