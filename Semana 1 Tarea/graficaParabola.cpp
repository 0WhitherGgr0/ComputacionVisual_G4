#include <GL/glut.h>
#include <stdio.h>

// Coeficientes de la parábola y = ax^2 + bx + c
float a, b, c;
// Rango para el eje x
float xmin, xmax;

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xmin - 10, xmax + 10, -100, 100, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void write_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void draw_parabola() {
	float x, y;
	for (x = xmin; x <= xmax; x += 0.1) {
		y = a * x * x + b * x + c;
		write_pixel((int)x, (int)y);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0); // Color blanco para la parábola
	glLoadIdentity();
	draw_parabola();
	glFlush();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0); // Fondo negro
}

int main(int argc, char **argv) {
	printf("Ingrese los coeficientes a, b, c de la parábola (y = ax^2 + bx + c):\n");
	scanf("%f %f %f", &a, &b, &c);
	printf("Ingrese el rango mínimo y máximo de x (xmin xmax):\n");
	scanf("%f %f", &xmin, &xmax);
	
	
	/*
	Valores para la parabola: 
		Valor 1:
		0.05 0.0 0
		-50 50
	
		Valor 2:
		0.01 0.0 0
		-100 100
	*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Parabola Drawing in OpenGL - User Input");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
